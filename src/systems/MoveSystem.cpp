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
    auto entities = entityManager.getEntitiesByComponents(42); // Get tout ceux qui on un move comp & un input

    for (auto &entity : entities) {
        auto inputComp = entity.getComponent<Indie::Components::InputComponent>(42); // get le input comp
        auto moveComp = entity.getComponent<Indie::Components::MoveComponent>(42); // get le move comp
        moveComp->setUp(inputComp->isKeyPressed(Indie::Components::InputComponent::UP));
        moveComp->setDown(inputComp->isKeyPressed(Indie::Components::InputComponent::DOWN));
        moveComp->setRight(inputComp->isKeyPressed(Indie::Components::InputComponent::RIGHT));
        moveComp->setLeft(inputComp->isKeyPressed(Indie::Components::InputComponent::LEFT));
        moveComp->setDrop(inputComp->isKeyPressed(Indie::Components::InputComponent::DROP));
    }
}
