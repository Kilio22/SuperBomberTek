/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** GameComponent
*/

#include "GameComponent.hpp"

Indie::Components::GameComponent::GameComponent()
    : gameStatus(MATCH_PLAY::NOT_ENDED)
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
