/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** TimerComponent
*/

#include "TimerComponent.hpp"

Indie::Components::TimerComponent::TimerComponent(irr::f32 timeToEnd)
    : timePassed(0.f), timeToEnd(timeToEnd)
{
}

irr::f32 Indie::Components::TimerComponent::getTimePassed(void) const
{
    return this->timePassed;
}

irr::f32 Indie::Components::TimerComponent::getTimeToEnd(void) const
{
    return this->timeToEnd;
}

void Indie::Components::TimerComponent::setTimePassed(irr::f32 timePassed)
{
    this->timePassed = timePassed;
}

void Indie::Components::TimerComponent::setTimeToEnd(irr::f32 timeToEnd)
{
    this->timeToEnd = timeToEnd;
}
