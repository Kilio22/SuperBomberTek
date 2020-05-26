/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** RotationSystem
*/

#include "RotationSystem.hpp"
#include "Components.h"

void Indie::Systems::RotationSystem::onUpdate(irr::f32, EntityManager &entityManager) const
{
    for (auto entity : entityManager.each<Indie::Components::RotationComponent, Indie::Components::MoveComponent>()) {
        auto moveComponent = entity->getComponent<Indie::Components::MoveComponent>();
        auto rotationComponent = entity->getComponent<Indie::Components::RotationComponent>();

        if (entity->has<Components::TimerComponent>() == true && entity->has<Components::PlayerComponent>() == true)
            continue;
        if (moveComponent->getUp() == true) {
            rotationComponent->setYAngle(180);
        } else if (moveComponent->getDown() == true) {
            rotationComponent->setYAngle(0);
        } else if (moveComponent->getRight() == true) {
            rotationComponent->setYAngle(270);
        } else if (moveComponent->getLeft() == true) {
            rotationComponent->setYAngle(90);
        }
    }
}
