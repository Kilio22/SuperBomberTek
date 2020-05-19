/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** BombUpComponent
*/

#include "WallPassComponent.hpp"

Indie::Components::WallPassComponent::WallPassComponent()
    : AComponent(0)
{
    this->canPass = false;
}

bool Indie::Components::WallPassComponent::getWallPass() const
{
    return this->canPass;
}

void Indie::Components::WallPassComponent::setWallPass(bool status)
{
    this->canPass = status;
}

