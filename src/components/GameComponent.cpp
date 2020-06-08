/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** GameComponent
*/

#include "GameComponent.hpp"

Indie::Components::GameComponent::GameComponent(irr::f32 timeToEnd)
    : gameStatus(MATCH_PLAY::NOT_ENDED)
    , timeToEnd(timeToEnd)
{
}

Indie::MATCH_PLAY Indie::Components::GameComponent::getGameStatus() const
{
    return this->gameStatus;
}

void Indie::Components::GameComponent::setGameStatus(MATCH_PLAY status)
{
    this->gameStatus = status;
}

irr::f32 Indie::Components::GameComponent::getTimeToEnd(void) const
{
    return this->timeToEnd;
}

void Indie::Components::GameComponent::setTimeToEnd(irr::f32 value)
{
    this->timeToEnd = value;
}
