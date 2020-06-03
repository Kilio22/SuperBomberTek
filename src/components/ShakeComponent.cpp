/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** ShakeComponent | Author: Kylian BALAN - kylian.balan@epitech.eu
*/

#include "ShakeComponent.hpp"

Indie::Components::ShakeComponent::ShakeComponent()
    : initialPositon(138.577f, 280.f, 65.f), initialTarget(138.593f, -34.13f, 121.f), deltaTime(0.f), isShaking(false)
{
}

bool Indie::Components::ShakeComponent::getIsShaking(void) const
{
    return this->isShaking;
}

irr::f32 Indie::Components::ShakeComponent::getDeltaTime(void) const
{
    return this->deltaTime;
}

const irr::core::vector3df &Indie::Components::ShakeComponent::getInitialPosition(void) const
{
    return this->initialPositon;
}

const irr::core::vector3df &Indie::Components::ShakeComponent::getInitialTarget(void) const
{
    return this->initialTarget;
}

void Indie::Components::ShakeComponent::setIsShaking(bool value)
{
    this->isShaking = value;
}

void Indie::Components::ShakeComponent::setDeltaTime(irr::f32 value)
{
    this->deltaTime = value;
}
