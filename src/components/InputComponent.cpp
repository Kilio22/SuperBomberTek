/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** InputComponent
*/

#include <irrlicht.h>
#include <algorithm>
#include "InputComponent.hpp"

Indie::Components::InputComponent::InputComponent(std::map<irr::EKEY_CODE, KEY_TYPE> keys)
    : keys(keys)
{
    for (auto it = keys.begin(); it != keys.end(); ++it) {
        this->keysState[it->first] = false;
    }
}

bool Indie::Components::InputComponent::isKeyPressed(KEY_TYPE key) const
{
    auto toFind = std::find_if(this->keys.begin(), this->keys.end(), [key](const std::pair<irr::EKEY_CODE, KEY_TYPE> &value) {return value.second == key;});

    if (toFind == this->keys.end())
        return false;
    auto keyState = this->keysState.find(toFind->first);
    if (keyState == this->keysState.end())
        return false;
    return keyState->second;
}

const std::map<irr::EKEY_CODE, Indie::Components::KEY_TYPE> &Indie::Components::InputComponent::getKeys() const
{
    return this->keys;
}

const std::map<irr::EKEY_CODE, bool> &Indie::Components::InputComponent::getKeysState() const
{
    return this->keysState;
}

void Indie::Components::InputComponent::setKeys(std::map<irr::EKEY_CODE, KEY_TYPE> newKeys)
{
    this->keys = newKeys;
    this->keysState.clear();
    for (auto it = keys.begin(); it != keys.end(); ++it) {
        this->keysState.at(it->first) = false;
    }
}
void Indie::Components::InputComponent::setKeysState(std::map<irr::EKEY_CODE, bool> newKeyStates)
{
    this->keysState = newKeyStates;
}

Indie::Components::KEY_TYPE Indie::Components::InputComponent::getKeyType(irr::EKEY_CODE key) const
{
    auto toFind = std::find_if(this->keys.begin(), this->keys.end(), [key](const std::pair<irr::EKEY_CODE, KEY_TYPE> &value) {return value.first == key;});

    if (toFind == this->keys.end())
        return KEY_TYPE::NONE;
    return toFind->second;
}
