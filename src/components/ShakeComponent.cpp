/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** ShakeComponent | Author: Kylian BALAN - kylian.balan@epitech.eu
*/

#include "ShakeComponent.hpp"

Indie::Components::ShakeComponent::ShakeComponent()
    : initialPositon(138.577f, 280.f, 65.f), initialTarget(138.593f, -34.13, 121.f), startingTime(0), isShaking(false)
{
}

bool Indie::Components::ShakeComponent::getIsShaking(void) const
{
    return this->isShaking;
}

irr::u32 Indie::Components::ShakeComponent::getStartingTime(void) const
{
    return this->startingTime;
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

void Indie::Components::ShakeComponent::setStartingTime(irr::u32 value)
{
    this->startingTime = value;
}
