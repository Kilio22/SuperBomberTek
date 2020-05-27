/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** InputSystem
*/

#include "InputSystem.hpp"
#include "Components.h"
#include "EntityManager.hpp"
#include <iostream>

std::map<irr::EKEY_CODE, bool> Indie::Systems::InputSystem::updateKeys(
    std::map<irr::EKEY_CODE, bool> keysStates, Indie::Components::InputComponent *inputComponent) const
{
    for (auto &keyState : keysStates) {
        if (inputComponent->getKeyType(keyState.first) == Indie::Components::KEY_TYPE::DROP) {
            keyState.second = EventHandler::getInstance().isKeyReleased(keyState.first);
        } else {
            keyState.second = EventHandler::getInstance().isKeyPressed(keyState.first);
        }
    }
    return keysStates;
}

void Indie::Systems::InputSystem::onUpdate(irr::f32, EntityManager &entityManager) const
{
    for (auto entity : entityManager.each<Indie::Components::InputComponent>()) {
        auto inputComponent = entity->getComponent<Indie::Components::InputComponent>();

        inputComponent->setKeysState(this->updateKeys(inputComponent->getKeysState(), inputComponent));
    }
}
