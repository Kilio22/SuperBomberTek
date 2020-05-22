/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** InputSystem
*/

#include "InputSystem.hpp"
#include "EntityManager.hpp"
#include "Components.h"

Indie::Systems::InputSystem::InputSystem()
    : eventHandler(EventHandler::getInstance())
{}

std::map<irr::EKEY_CODE, bool> Indie::Systems::InputSystem::updateKeys(std::map<irr::EKEY_CODE, bool> keysStates, Indie::Components::InputComponent *inputComponent) const
{
    for (auto &keyState : keysStates) {
        if (inputComponent->getKeyType(keyState.first) == Indie::Components::DROP) {
            keyState.second = this->eventHandler.isKeyReleased(keyState.first);
        } else {
            keyState.second = this->eventHandler.isKeyPressed(keyState.first);
        }
    }
    return keysStates;
}

void Indie::Systems::InputSystem::onUpdate(irr::f32 deltaTime, EntityManager &entityManager, const ContextManager &) const
{
    for (auto entity : entityManager.each<Indie::Components::InputComponent>()) {
        auto inputComponent = entity->getComponent<Indie::Components::InputComponent>();

        inputComponent->setKeysState(this->updateKeys(inputComponent->getKeysState(), inputComponent));
    }
}
