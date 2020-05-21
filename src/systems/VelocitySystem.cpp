/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** VelocitySystem
*/

#include "VelocitySystem.hpp"
#include "PositionComponent.hpp"
#include "VelocityComponent.hpp"
#include "InputComponent.hpp"
#include "MoveComponent.hpp"

void Indie::Systems::VelocitySystem::onUpdate(int ticks, EntityManager &entityManager) const
{
    for (auto entity : entityManager.each<Indie::Components::PositionComponent, Indie::Components::MoveComponent, Indie::Components::VelocityComponent>()) {
        auto moveComponent = entity->getComponent<Indie::Components::MoveComponent>();
        auto positionComponent = entity->getComponent<Indie::Components::PositionComponent>();
        auto velocityComponent = entity->getComponent<Indie::Components::VelocityComponent>();
        irr::core::vector3df posVector = positionComponent->getPosition();

        velocityComponent->setVelocity(0);
        if (moveComponent->getUp() == true) {
            velocityComponent->setVelocity(1);
            posVector.Z += 1;
        }
        if (moveComponent->getDown() == true) {
            velocityComponent->setVelocity(1);
            posVector.Z -= 1;
        }
        if (moveComponent->getRight() == true) {
            velocityComponent->setVelocity(1);
            posVector.X += 1;
        }
        if (moveComponent->getLeft() == true) {
            velocityComponent->setVelocity(1);
            posVector.X -= 1;
        }
        positionComponent->setPosition(posVector);
    }
}