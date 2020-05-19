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

std::map<irr::EKEY_CODE, bool> Indie::Systems::InputSystem::updateKeys(std::map<irr::EKEY_CODE, bool> keysStates, std::shared_ptr<Indie::Components::InputComponent> &inputComp)
{
    for (auto &keyState : keysStates) {
        if (inputComp->getKeyType(keyState.first) == Indie::Components::InputComponent::DROP) {
            keyState.second = this->eventHandler.isKeyReleased(keyState.first);
        } else {
            keyState.second = this->eventHandler.isKeyPressed(keyState.first);
        }
    }
    return keysStates;
}

void Indie::Systems::InputSystem::onUpdate(int ticks, EntityManager &entityManager)
{
    auto entities = entityManager.getEntitiesByComponents(2); // on get tout ceux qui on un inputComp

    for (auto &entity : entities) {
        auto inputComp = entity.getComponent<Indie::Components::InputComponent>(2);
        inputComp->setKeysState(this->updateKeys(inputComp->getKeysState(), inputComp));
    }
}
