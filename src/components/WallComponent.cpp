/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** WallComponent
*/

#include "WallComponent.hpp"

Indie::Components::WallComponent::WallComponent(bool canBeDestroyed)
    : canBeDestroyed(canBeDestroyed)
{
}

bool Indie::Components::WallComponent::getCanBeDestroyed() const
{
    return this->canBeDestroyed;
}
