/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** RotationSystem
*/

#include "RotationSystem.hpp"
#include "Components.h"

void Indie::Systems::RotationSystem::onUpdate(irr::f32 deltaTime, EntityManager &entityManager) const
{
    for (auto entity : entityManager.each<Indie::Components::RotationComponent, Indie::Components::MoveComponent>()) {
        auto moveComponent = entity->getComponent<Indie::Components::MoveComponent>();
        auto rotationComponent = entity->getComponent<Indie::Components::RotationComponent>();

        if (moveComponent->getUp() == true) {
            rotationComponent->setAngle(180);
        } else if (moveComponent->getDown() == true) {
            rotationComponent->setAngle(0);
        } else if (moveComponent->getRight() == true) {
            rotationComponent->setAngle(270);
        } else if (moveComponent->getLeft() == true) {
            rotationComponent->setAngle(90);
        }
    }
}
