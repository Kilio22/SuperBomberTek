/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** PowerUpComponent
*/

#include "PowerUpComponent.hpp"

Indie::Components::PowerUpComponent::PowerUpComponent(Components::POWERUP_TYPE type)
    : type(type)
{
}

Indie::Components::POWERUP_TYPE Indie::Components::PowerUpComponent::getType(void) const
{
    return this->type;
}
