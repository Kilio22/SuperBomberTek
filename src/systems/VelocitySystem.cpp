/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** VelocitySystem
*/

#include "VelocitySystem.hpp"
#include "Components.h"

using namespace Indie::Components;

void Indie::Systems::VelocitySystem::onUpdate(irr::f32 deltaTime, EntityManager &entityManager) const
{
    for (auto entity : entityManager.each<PositionComponent, MoveComponent, VelocityComponent, PlayerComponent>()) {
        auto moveComponent = entity->getComponent<MoveComponent>();
        auto positionComponent = entity->getComponent<PositionComponent>();
        auto velocityComponent = entity->getComponent<VelocityComponent>();
        auto playerComponent = entity->getComponent<PlayerComponent>();
        irr::core::vector3df posVector = positionComponent->getPosition();
        irr::f32 velocity = 20.0f + playerComponent->getVelocityLevel() * 5;

        velocityComponent->setVelocity(0);
        if (entity->has<Components::TimerComponent>())
            continue;
        if (moveComponent->getLeft() == true && moveComponent->getRight() == true)
            continue;
        if (moveComponent->getUp() == true && moveComponent->getDown() == true)
            continue;
        if (moveComponent->getUp() == true) {
            velocityComponent->setVelocity(velocity);
            posVector.Z += velocity * deltaTime;
        }
        if (moveComponent->getDown() == true) {
            velocityComponent->setVelocity(velocity);
            posVector.Z -= velocity * deltaTime;
        }
        if (moveComponent->getRight() == true) {
            velocityComponent->setVelocity(velocity);
            posVector.X += velocity * deltaTime;
        }
        if (moveComponent->getLeft() == true) {
            velocityComponent->setVelocity(velocity);
            posVector.X -= velocity * deltaTime;
        }
        positionComponent->setPosition(posVector);
    }
}