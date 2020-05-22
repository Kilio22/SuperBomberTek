/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** MoveSystem
*/

#include "MoveSystem.hpp"
#include "Components.h"

void Indie::Systems::MoveSystem::onUpdate(int ticks, Indie::EntityManager &entityManager, const ContextManager &) const
{
    for (auto entity : entityManager.each<Indie::Components::MoveComponent, Indie::Components::InputComponent>()) {
        auto inputComponent = entity->getComponent<Indie::Components::InputComponent>();
        auto moveComponent = entity->getComponent<Indie::Components::MoveComponent>();

        moveComponent->setUp(inputComponent->isKeyPressed(Indie::Components::UP));
        moveComponent->setDown(inputComponent->isKeyPressed(Indie::Components::DOWN));
        moveComponent->setRight(inputComponent->isKeyPressed(Indie::Components::RIGHT));
        moveComponent->setLeft(inputComponent->isKeyPressed(Indie::Components::LEFT));
        moveComponent->setDrop(inputComponent->isKeyPressed(Indie::Components::DROP));
    }
}
