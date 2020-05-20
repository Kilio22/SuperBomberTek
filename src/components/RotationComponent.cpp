/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** RoationComponent
*/

#include "RotationComponent.hpp"

Indie::Components::RotationComponent::RotationComponent()
    : angle(irr::core::vector3df(0, 180, 0))
{}

irr::core::vector3df Indie::Components::RotationComponent::getAngle()
{
    return this->angle;
}

void Indie::Components::RotationComponent::setAngle(float newAngle)
{
    this->angle.Y = newAngle;
}
