/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** TimerTickSystem
*/

#include "TimerTickSystem.hpp"
#include "TimerComponent.hpp"

using namespace Indie::Components;

void Indie::Systems::TimerTickSystem::onUpdate(irr::f32 deltaTime, EntityManager &entityManager) const
{
    for (auto entity : entityManager.each<TimerComponent>()) {
        auto timer = entity->getComponent<TimerComponent>();

        timer->setTimePassed(timer->getTimePassed() + deltaTime);
    }
}
