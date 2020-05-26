/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** RoationComponent
*/

#include "RotationComponent.hpp"

Indie::Components::RotationComponent::RotationComponent(float angleY, float angleX)
    : angle(irr::core::vector3df(angleX, angleY, 0))
{}

const irr::core::vector3df &Indie::Components::RotationComponent::getAngle() const
{
    return this->angle;
}

void Indie::Components::RotationComponent::setYAngle(float newAngle)
{
    this->angle.Y = newAngle;
}

void Indie::Components::RotationComponent::setXAngle(float newAngle)
{
    this->angle.X = newAngle;
}
