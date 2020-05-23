/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** EventHandler
*/

#include <iostream>
#include "EventHandler.hpp"

Indie::EventHandler &Indie::EventHandler::getInstance()
{
    static EventHandler instance;

    return instance;
}

Indie::EventHandler::EventHandler()
    : keysStatus(irr::KEY_KEY_CODES_COUNT, false)
    , keysStatusOnce(irr::KEY_KEY_CODES_COUNT, false)
    , keysStatusReleased(irr::KEY_KEY_CODES_COUNT, false)
{
}

bool Indie::EventHandler::OnEvent(const irr::SEvent &event)
{
    if (event.EventType == irr::EET_KEY_INPUT_EVENT) {
        if (event.KeyInput.PressedDown == true) {
            this->keysStatus.at(event.KeyInput.Key) = true;
            this->keysStatusOnce.at(event.KeyInput.Key) = true;
        } else {
            this->keysStatus.at(event.KeyInput.Key) = false;
            this->keysStatusReleased.at(event.KeyInput.Key) = true;
        }
        return true;
    }
    return false;
}

bool Indie::EventHandler::isKeyPressed(irr::EKEY_CODE key) const
{
    if (key > irr::KEY_KEY_CODES_COUNT) {
        return false;
    }
    return this->keysStatus.at(key);
}

bool Indie::EventHandler::isKeyPressedAtOnce(irr::EKEY_CODE key) const
{
    if (key > irr::KEY_KEY_CODES_COUNT) {
        return false;
    }
    return this->keysStatusOnce.at(key);
}

bool Indie::EventHandler::isKeyReleased(irr::EKEY_CODE key) const
{
    if (key > irr::KEY_KEY_CODES_COUNT) {
        return false;
    }
    return this->keysStatusReleased.at(key);
}

void Indie::EventHandler::resetKeys(void)
{
    this->keysStatusOnce.assign(irr::KEY_KEY_CODES_COUNT, false);
    this->keysStatusReleased.assign(irr::KEY_KEY_CODES_COUNT, false);
}
