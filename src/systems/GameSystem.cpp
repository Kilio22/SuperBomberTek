/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** GameSystem
*/

#include "GameSystem.hpp"
#include "AIComponent.hpp"
#include "PauseScene.hpp"
#include "PlayerComponent.hpp"
#include "RenderComponent.hpp"

using namespace Indie::Components;

void Indie::Systems::GameSystem::onUpdate(irr::f32, EntityManager &entityManager) const
{
    auto &sceneManager = ServiceLocator::getInstance().get<SceneManager>();
    auto [playerCount, humanCount] = this->countPlayers(entityManager);

    if (EventHandler::getInstance().isKeyPressed(irr::EKEY_CODE::KEY_ESCAPE) == true) {
        for (auto entity : entityManager.each<RenderComponent>()) {
            entity->getComponent<RenderComponent>()->getMesh()->setAnimationSpeed(0.f);
        }
        sceneManager.setSceneUpdateActive(false);
        sceneManager.setSceneRenderActive(false);
        sceneManager.setSubScene<PauseScene>();
    }
    // On fait attention au scénario: "La touche pause est appuyée sur la même frame que quand la partie se termine."
    // (Parce que la subScene est set à PauseScene)
    if (playerCount == 0) {
        std::cout << "Game ended with a draw." << std::endl;
    } else if (humanCount == 0) {
        std::cout << "Game ended with a loss." << std::endl;
    } else if (playerCount == 1) {
        std::cout << "Game ended with a win." << std::endl;
    }
}

std::pair<unsigned int, unsigned int> Indie::Systems::GameSystem::countPlayers(EntityManager &entityManager) const
{
    unsigned int playerCount = 0;
    unsigned int humanCount = 0;

    for (auto entity : entityManager.each<PlayerComponent>()) {
        if (entity->getComponent<PlayerComponent>()->isDead())
            continue;
        ++playerCount;
        if (!entity->has<AIComponent>())
            ++humanCount;
    }
    return { playerCount, humanCount };
}
