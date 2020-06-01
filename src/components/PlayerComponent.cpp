/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** PlayerComponent
*/

#include "PlayerComponent.hpp"

Indie::Components::PlayerComponent::PlayerComponent(const std::string &playerNb, Components::PlayerComponent::PLAYER_COLOR playerColor)
    : bombsRange(2)
    , maxBombNb(1)
    , currentBombNb(1)
    , velocityLevel(1)
    , wallPass(false)
    , name("Player " + playerNb)
    , playerColor(playerColor)
{
}

unsigned int Indie::Components::PlayerComponent::getBombsRange(void) const
{
    return this->bombsRange;
}

unsigned int Indie::Components::PlayerComponent::getMaxBombNb(void) const
{
    return this->maxBombNb;
}

unsigned int Indie::Components::PlayerComponent::getCurrentBombNb(void) const
{
    return this->currentBombNb;
}

unsigned int Indie::Components::PlayerComponent::getVelocityLevel(void) const
{
    return this->velocityLevel;
}

bool Indie::Components::PlayerComponent::getWallPass(void) const
{
    return this->wallPass;
}

const std::string &Indie::Components::PlayerComponent::getName(void) const
{
    return this->name;
}

const Indie::Components::PlayerComponent::PLAYER_COLOR &Indie::Components::PlayerComponent::getPlayerColor(void) const
{
    return this->playerColor;
}

void Indie::Components::PlayerComponent::setBombsRange(unsigned int value)
{
    this->bombsRange = value;
}

void Indie::Components::PlayerComponent::setMaxBombNb(unsigned int value)
{
    this->maxBombNb = value;
}

void Indie::Components::PlayerComponent::setCurrentBombNb(unsigned int value)
{
    this->currentBombNb = value;
}

void Indie::Components::PlayerComponent::setVelocityLevel(unsigned int value)
{
    this->velocityLevel = value;
}

void Indie::Components::PlayerComponent::setWallPass(bool value)
{
    this->wallPass = value;
}