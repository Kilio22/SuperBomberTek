/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** TimerComponent
*/

#include "TimerComponent.hpp"

Indie::Components::TimerComponent::TimerComponent(irr::f32 seconds)
    : ticks(0.f), seconds(seconds)
{
}

irr::f32 Indie::Components::TimerComponent::getTicks(void) const
{
    return this->ticks;
}

irr::f32 Indie::Components::TimerComponent::getSeconds(void) const
{
    return this->seconds;
}

void Indie::Components::TimerComponent::setTicks(irr::f32 value)
{
    this->ticks = value;
}

void Indie::Components::TimerComponent::setSeconds(irr::f32 value)
{
    this->seconds = value;
}
