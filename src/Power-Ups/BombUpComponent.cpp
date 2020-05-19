/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** BombUpComponent
*/

#include "BombUpComponent.hpp"

Indie::Components::BombUpComponent::BombUpComponent()
{
    this->numberBomb = 1;
}

int Indie::Components::BombUpComponent::getNumberBomb() const
{
    return this->numberBomb;
}

void Indie::Components::BombUpComponent::setNumberBomb(int numberBomb)
{
    this->numberBomb = numberBomb;
}

