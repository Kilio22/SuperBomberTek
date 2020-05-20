/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** MoveSystem
*/

#include "MoveSystem.hpp"
#include "MoveComponent.hpp"
#include "EventHandler.hpp"
#include "InputComponent.hpp"

void onUpdate(int ticks, Indie::EntityManager &entityManager)
{
    for (auto entity : entityManager.each<Indie::Components::MoveComponent, Indie::Components::InputComponent>()) {
        auto inputComponent = entity->getComponent<Indie::Components::InputComponent>();
        auto moveComponent = entity->getComponent<Indie::Components::MoveComponent>();

        moveComponent->setUp(inputComponent->isKeyPressed(Indie::Components::InputComponent::UP));
        moveComponent->setDown(inputComponent->isKeyPressed(Indie::Components::InputComponent::DOWN));
        moveComponent->setRight(inputComponent->isKeyPressed(Indie::Components::InputComponent::RIGHT));
        moveComponent->setLeft(inputComponent->isKeyPressed(Indie::Components::InputComponent::LEFT));
        moveComponent->setDrop(inputComponent->isKeyPressed(Indie::Components::InputComponent::DROP));
    }
}
