/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** PlayerSystem
*/

#include "PlayerSystem.hpp"
#include "PlayerComponent.hpp"
#include "TimerComponent.hpp"

using namespace Indie::Components;

void Indie::Systems::PlayerSystem::onUpdate(irr::f32 deltaTime, EntityManager &entityManager) const
{
    for (auto entity : entityManager.each<PlayerComponent>()) {
        auto player = entity->getComponent<PlayerComponent>();

        // while (player->getXpCount() >= player->getXpToLevelUp()) {
        //     player->setXpCount(player->getXpCount() - player->getXpToLevelUp());
        //     player->setLevelCount(player->getLevelCount() + 1);
        // }
        if (entity->has<TimerComponent>()) {
            auto timer = entity->getComponent<TimerComponent>();

            if (timer->getTimePassed() >= timer->getTimeToEnd()) {
                auto newPlayer = *player;

                entity->removeAllComponents();
                entity->addComponent<PlayerComponent>(newPlayer);
            }
        }
    }
}
