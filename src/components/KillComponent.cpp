/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** KillComponent
*/

#include "KillComponent.hpp"

Indie::Components::KillComponent::KillComponent(int ownerId)
    : ownerId(ownerId)
{
}

int Indie::Components::KillComponent::getOwnerId() const
{
    return this->ownerId;
}
