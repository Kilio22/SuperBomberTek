/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** PlayerComponent
*/

#include "PlayerComponent.hpp"

Indie::Components::PlayerComponent::PlayerComponent(const std::string &playerNb)
    : bombsRange(2), maxBombNb(4), currentBombNb(4), velocity(25.f), wallPass(false), name("Player " + playerNb)
{
}

unsigned int Indie::Components::PlayerComponent::getBombsRange(void) const
{
    return this->bombsRange;
}

unsigned int Indie::Components::PlayerComponent::getMaxBombNb(void) const
{
    return this->maxBombNb;
}

unsigned int Indie::Components::PlayerComponent::getCurrentBombNb(void) const
{
    return this->currentBombNb;
}

irr::f32 Indie::Components::PlayerComponent::getVelocity(void) const
{
    return this->velocity;
}

bool Indie::Components::PlayerComponent::getWallPass(void) const
{
    return this->wallPass;
}

const std::string &Indie::Components::PlayerComponent::getName(void) const
{
    return this->name;
}

void Indie::Components::PlayerComponent::setBombsRange(unsigned int value)
{
    this->bombsRange = value;
}

void Indie::Components::PlayerComponent::setMaxBombNb(unsigned int value)
{
    this->maxBombNb = value;
}

void Indie::Components::PlayerComponent::setCurrentBombNb(unsigned int value)
{
    this->currentBombNb = value;
}

void Indie::Components::PlayerComponent::setVelocity(irr::f32 value)
{
    this->velocity = value;
}

void Indie::Components::PlayerComponent::setWallPass(bool value)
{
    this->wallPass = value;
}