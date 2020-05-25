/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** BombComponent
*/

#include "BombComponent.hpp"

Indie::Components::BombComponent::BombComponent(int idOwner, u_int32_t range)
    : idOwner(idOwner)
    , range(range)
{
}

u_int32_t Indie::Components::BombComponent::getRange() const
{
    return this->range;
}

int Indie::Components::BombComponent::getIdOwner() const
{
    return this->idOwner;
}

void Indie::Components::BombComponent::setRange(u_int32_t range)
{
    this->range = range;
}
