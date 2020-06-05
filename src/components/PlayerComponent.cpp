/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** PlayerComponent
*/

#include "PlayerComponent.hpp"

Indie::Components::PlayerComponent::PlayerComponent(
    const std::string &name, Components::PlayerComponent::PLAYER_COLOR playerColor, PLAYER_START_POSITION startPosition, bool isHuman)
    : _isHuman(isHuman)
    , bombsRange(2)
    , maxBombNb(1)
    , currentBombNb(1)
    , velocityLevel(1)
    , xp(0)
    , score(0)
    , wallPass(false)
    , _isDead(false)
    , name(name)
    , playerColor(playerColor)
    , startPosition(startPosition)
{
}

bool Indie::Components::PlayerComponent::isHuman(void) const
{
    return this->_isHuman;
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

unsigned int Indie::Components::PlayerComponent::getXp(void) const
{
    return this->xp;
}

int Indie::Components::PlayerComponent::getScore(void) const
{
    return this->score;
}

bool Indie::Components::PlayerComponent::getWallPass(void) const
{
    return this->wallPass;
}

bool Indie::Components::PlayerComponent::isDead(void) const
{
    return this->_isDead;
}

const std::string &Indie::Components::PlayerComponent::getName(void) const
{
    return this->name;
}

Indie::Components::PlayerComponent::PLAYER_COLOR Indie::Components::PlayerComponent::getPlayerColor(void) const
{
    return this->playerColor;
}

Indie::Components::PlayerComponent::PLAYER_START_POSITION Indie::Components::PlayerComponent::getStartPosition(void) const
{
    return this->startPosition;
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

void Indie::Components::PlayerComponent::setXpCount(unsigned int value)
{
    this->xp = value;
}

void Indie::Components::PlayerComponent::setScore(int score)
{
    this->score = score;
}

void Indie::Components::PlayerComponent::setWallPass(bool value)
{
    this->wallPass = value;
}

void Indie::Components::PlayerComponent::setIsDead(bool value)
{
    this->_isDead = value;
}
