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
    , exploded(false)
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

bool Indie::Components::BombComponent::hasExploded() const
{
    return this->exploded;
}

void Indie::Components::BombComponent::setRange(unsigned int range)
{
    this->range = range;
}

void Indie::Components::BombComponent::setExploded(bool exploded)
{
    this->exploded = exploded;
}
