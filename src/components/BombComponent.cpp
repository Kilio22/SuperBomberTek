/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** BombComponent
*/

#include "BombComponent.hpp"

Indie::Components::BombComponent::BombComponent(int idOwner, unsigned int range)
    : idOwner(idOwner)
    , range(range)
{
}

unsigned int Indie::Components::BombComponent::getRange() const
{
    return this->range;
}

int Indie::Components::BombComponent::getIdOwner() const
{
    return this->idOwner;
}

void Indie::Components::BombComponent::setRange(unsigned int range)
{
    this->range = range;
}
