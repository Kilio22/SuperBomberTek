/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** VelocityComponent
*/

#include "VelocityComponent.hpp"

Indie::Components::VelocityComponent::VelocityComponent()
    : velocity(0)
{
}

float Indie::Components::VelocityComponent::getVelocity()
{
    return this->velocity;
}

void Indie::Components::VelocityComponent::setVelocity(float newVel)
{
    this->velocity = newVel;
}