/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** PositionComponent
*/

#include "PositionComponent.hpp"

Indie::Components::PositionComponent::PositionComponent(float posX, float posY, float posZ)
    : position(posX, posY, posZ)
{}

irr::core::vector3df Indie::Components::PositionComponent::getPosition()
{
    return this->position;
}

void Indie::Components::PositionComponent::setPosition(irr::core::vector3df position)
{
    this->position = position;
}
