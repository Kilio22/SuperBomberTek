/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** InputSystem
*/

#include "InputSystem.hpp"
#include "InputComponent.hpp"
#include "EntityManager.hpp"

Indie::Systems::InputSystem::InputSystem()
    : eventHandler(EventHandler::getInstance())
{}

std::map<irr::EKEY_CODE, bool> Indie::Systems::InputSystem::updateKeys(std::map<irr::EKEY_CODE, bool> keysStates, Indie::Components::InputComponent *inputComponent)
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

void Indie::Systems::InputSystem::onUpdate(int ticks, EntityManager &entityManager)
{
    for (auto entity : entityManager.each<Indie::Components::InputComponent>()) {
        auto inputComponent = entity->getComponent<Indie::Components::InputComponent>();

        inputComponent->setKeysState(this->updateKeys(inputComponent->getKeysState(), inputComponent));
    }
}
