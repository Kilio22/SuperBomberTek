/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** BombUpComponent
*/

#include "KickBombComponent.hpp"

Indie::Components::KickBombComponent::KickBombComponent()
    : AComponent(0)
{
    this->canKick = false;
}

bool Indie::Components::KickBombComponent::getKickStatus() const
{
    return this->canKick;
}

void Indie::Components::KickBombComponent::setKickStatus(bool status)
{
    this->canKick = status;
}

