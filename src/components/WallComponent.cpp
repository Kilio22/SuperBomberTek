/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** WallComponent
*/

#include "WallComponent.hpp"

Indie::Components::WallComponent::WallComponent()
    : canBeDestroyed(false)
{
}

bool Indie::Components::WallComponent::getCanBeDestroyed() const
{
    return this->canBeDestroyed;
}

void Indie::Components::WallComponent::setCanBeDestroyed(bool value)
{
    this->canBeDestroyed = value;
}
