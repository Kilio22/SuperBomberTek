/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** GameSystem
*/

#include "GameSystem.hpp"
#include "AIComponent.hpp"
#include "EndScene.hpp"
#include "PauseScene.hpp"
#include "Components.h"

using namespace Indie::Components;

void Indie::Systems::GameSystem::onUpdate(irr::f32, EntityManager &entityManager) const
{
    auto &sceneManager = ServiceLocator::getInstance().get<SceneManager>();
    auto game = entityManager.getUniqueEntity<GameComponent>()->getComponent<GameComponent>();

    if (game->getGameStatus() == MATCH_PLAY::NOT_ENDED && this->isGameEnded(entityManager, game)) {
        ServiceLocator::getInstance().get<MusicManager>().pauseMusic();
        for (auto entity : entityManager.each<PlayerComponent>()) {
            if (entity->has<MoveComponent>())
                entity->removeComponent<MoveComponent>();
            if (entity->has<HitboxComponent>())
                entity->removeComponent<HitboxComponent>();
            if (entity->has<VelocityComponent>())
                entity->getComponent<VelocityComponent>()->setVelocity(0);
        }
    }
    if (game->getGameStatus() == MATCH_PLAY::NOT_ENDED && EventHandler::getInstance().isKeyPressed(irr::EKEY_CODE::KEY_ESCAPE) == true) {
        for (auto entity : entityManager.each<RenderComponent>())
            entity->getComponent<RenderComponent>()->getMesh()->setAnimationSpeed(0.f);
        sceneManager.setSceneUpdateActive(false);
        sceneManager.setSceneRenderActive(false);
        sceneManager.setSubScene<PauseScene>();
    }
    if (game->getGameStatus() != MATCH_PLAY::NOT_ENDED && this->noTimersLeft(entityManager)) {
        this->endGame(entityManager, sceneManager, game->getGameStatus());
        entityManager.cleanup();
        sceneManager.setSceneUpdateActive(false);
        sceneManager.setSceneRenderActive(true);
        ServiceLocator::getInstance().get<MusicManager>().playMusic();
        sceneManager.setSubScene<EndScene>();
    }
}

bool Indie::Systems::GameSystem::isGameEnded(EntityManager &entityManager, GameComponent *game) const
{
    unsigned int playerCount = 0;
    unsigned int humanCount = 0;

    for (auto entity : entityManager.each<PlayerComponent>()) {
        auto player = entity->getComponent<PlayerComponent>();

        if (player->isDead())
            continue;
        ++playerCount;
        if (player->isHuman())
            ++humanCount;
    }
    if (playerCount == 0)
        game->setGameStatus(MATCH_PLAY::DRAW);
    else if (humanCount == 0)
        game->setGameStatus(MATCH_PLAY::LOSE);
    else if (playerCount == 1)
        game->setGameStatus(MATCH_PLAY::WIN);
    else
        return false;
    return true;
}

void Indie::Systems::GameSystem::endGame(EntityManager &entityManager, SceneManager &sceneManager, MATCH_PLAY endType) const
{
    EndGame stats;

    stats.matchPlay = endType;
    for (auto entity : entityManager.each<PlayerComponent>()) {
        auto player = entity->getComponent<PlayerComponent>();

        if (!player->isHuman())
            continue;
        if (endType == MATCH_PLAY::WIN && !player->isDead()) {
            stats.xp = player->getXp();
            stats.scores.insert(stats.scores.begin(), { player->getName(), player->getScore() });
        } else {
            stats.xp = 0;
            stats.scores.push_back({ player->getName(), player->getScore() });
        }
    }
    sceneManager.getScene<EndScene>()->setEndGame(stats);
}

bool Indie::Systems::GameSystem::noTimersLeft(EntityManager &entityManager) const
{
    for (auto entity : entityManager.each<TimerComponent>()) {
        if (entity->has<PowerUpComponent>() || entity->has<PowerDownComponent>())
            continue;
        return false;
    }
    return true;
}
