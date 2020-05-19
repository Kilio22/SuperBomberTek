/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** BombUpComponent
*/

#include "PowerComponent.hpp"

Indie::Components::PowerComponent::PowerComponent()
    : AComponent(0)
{
    this->power = 3;
}

int Indie::Components::PowerComponent::getPower() const
{
    return this->power;
}

void Indie::Components::PowerComponent::setPower(int power)
{
    this->power = power;
}

