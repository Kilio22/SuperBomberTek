/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** PowerDownComponent | Author: Kylian BALAN - kylian.balan@epitech.eu
*/

#include "PowerDownComponent.hpp"

Indie::Components::PowerDownComponent::PowerDownComponent(Indie::Components::POWERDOWN_TYPE type)
    : type(type)
{}

Indie::Components::POWERDOWN_TYPE Indie::Components::PowerDownComponent::getType(void) const
{
    return this->type;
}
