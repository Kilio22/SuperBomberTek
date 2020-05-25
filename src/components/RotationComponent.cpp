/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** RoationComponent
*/

#include "RotationComponent.hpp"

Indie::Components::RotationComponent::RotationComponent(float angle)
    : angle(irr::core::vector3df(0, angle, 0))
{}

const irr::core::vector3df &Indie::Components::RotationComponent::getAngle() const
{
    return this->angle;
}

void Indie::Components::RotationComponent::setAngle(float newAngle)
{
    this->angle.Y = newAngle;
}
