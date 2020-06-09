/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** TimerStopSystem
*/

#include "TimerStopSystem.hpp"
#include "TimerComponent.hpp"

using namespace Indie::Components;

void Indie::Systems::TimerStopSystem::onUpdate(irr::f32, EntityManager &entityManager) const
{
    for (auto entity : entityManager.each<TimerComponent>()) {
        auto timer = entity->getComponent<TimerComponent>();

        if (timer->getTimePassed() >= timer->getTimeToEnd())
            entity->needDestroy();
    }
}
