/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** MoveSystem
*/

#include "MoveSystem.hpp"
#include "Components.h"
#include "EventHandler.hpp"

void Indie::Systems::MoveSystem::onUpdate(irr::f32 deltaTime, Indie::EntityManager &entityManager, const ContextManager &) const
{
    for (auto entity : entityManager.each<Indie::Components::MoveComponent, Indie::Components::InputComponent>()) {
        auto inputComponent = entity->getComponent<Indie::Components::InputComponent>();
        auto moveComponent = entity->getComponent<Indie::Components::MoveComponent>();

        moveComponent->setUp(inputComponent->isKeyPressed(Indie::Components::KEY_TYPE::UP));
        moveComponent->setDown(inputComponent->isKeyPressed(Indie::Components::KEY_TYPE::DOWN));
        moveComponent->setRight(inputComponent->isKeyPressed(Indie::Components::KEY_TYPE::RIGHT));
        moveComponent->setLeft(inputComponent->isKeyPressed(Indie::Components::KEY_TYPE::LEFT));
        moveComponent->setDrop(inputComponent->isKeyPressed(Indie::Components::KEY_TYPE::DROP));
    }
    EventHandler::getInstance().resetKeys();
}
