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
#include "PlayerComponent.hpp"
#include "RenderComponent.hpp"

using namespace Indie::Components;

void Indie::Systems::GameSystem::onUpdate(irr::f32, EntityManager &entityManager) const
{
    auto &sceneManager = ServiceLocator::getInstance().get<SceneManager>();
    auto [playerCount, humanCount] = this->countPlayers(entityManager);
    MATCH_PLAY endType = MATCH_PLAY::NOT_ENDED;

    if (EventHandler::getInstance().isKeyPressed(irr::EKEY_CODE::KEY_ESCAPE) == true) {
        for (auto entity : entityManager.each<RenderComponent>())
            entity->getComponent<RenderComponent>()->getMesh()->setAnimationSpeed(0.f);
        sceneManager.setSceneUpdateActive(false);
        sceneManager.setSceneRenderActive(false);
        sceneManager.setSubScene<PauseScene>();
    }
    // On fait attention au scénario: "La touche pause est appuyée sur la même frame que quand la partie se termine."
    // (Parce que la subScene est set à PauseScene)
    if (playerCount == 0) {
        std::cout << "Game ended with a draw." << std::endl;
        endType = MATCH_PLAY::DRAW;
    } else if (humanCount == 0) {
        std::cout << "Game ended with a loss." << std::endl;
        endType = MATCH_PLAY::LOSE;
    } else if (playerCount == 1) {
        std::cout << "Game ended with a win." << std::endl;
        endType = MATCH_PLAY::WIN;
    }
    if (endType != MATCH_PLAY::NOT_ENDED) {
        this->endGame(entityManager, sceneManager, endType);
        for (auto entity : entityManager.each<RenderComponent>())
            entity->getComponent<RenderComponent>()->getMesh()->setAnimationSpeed(0.f);
        sceneManager.setSceneUpdateActive(false);
        sceneManager.setSceneRenderActive(false);
        sceneManager.setSubScene<EndScene>();
    }
}

std::pair<unsigned int, unsigned int> Indie::Systems::GameSystem::countPlayers(EntityManager &entityManager) const
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
    return { playerCount, humanCount };
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
