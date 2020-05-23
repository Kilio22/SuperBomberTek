/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** VelocitySystem
*/

#include "VelocitySystem.hpp"
#include "Components.h"

const irr::f32 Indie::Systems::VelocitySystem::VELOCITY = 25.0f;

void Indie::Systems::VelocitySystem::onUpdate(irr::f32 deltaTime, EntityManager &entityManager) const
{
    for (auto entity : entityManager.each<Indie::Components::PositionComponent, Indie::Components::MoveComponent, Indie::Components::VelocityComponent>()) {
        auto moveComponent = entity->getComponent<Indie::Components::MoveComponent>();
        auto positionComponent = entity->getComponent<Indie::Components::PositionComponent>();
        auto velocityComponent = entity->getComponent<Indie::Components::VelocityComponent>();
        irr::core::vector3df posVector = positionComponent->getPosition();

        velocityComponent->setVelocity(0);
        if (moveComponent->getLeft() == true && moveComponent->getRight() == true) {
            continue;
        }
        if (moveComponent->getUp() == true && moveComponent->getDown() == true) {
            continue;
        }
        if (moveComponent->getUp() == true) {
            velocityComponent->setVelocity(this->VELOCITY);
            posVector.Z += VELOCITY * deltaTime;
        }
        if (moveComponent->getDown() == true) {
            velocityComponent->setVelocity(this->VELOCITY);
            posVector.Z -= VELOCITY * deltaTime;
        }
        if (moveComponent->getRight() == true) {
            velocityComponent->setVelocity(this->VELOCITY);
            posVector.X += VELOCITY * deltaTime;
        }
        if (moveComponent->getLeft() == true) {
            velocityComponent->setVelocity(this->VELOCITY);
            posVector.X -= VELOCITY * deltaTime;
        }
        positionComponent->setPosition(posVector);
    }
}