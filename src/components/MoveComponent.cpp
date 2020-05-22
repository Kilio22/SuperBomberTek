/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** MoveComponent
*/

#include "MoveComponent.hpp"

Indie::Components::MoveComponent::MoveComponent()
    : up(false), down(false), left(false), right(false), drop(false)
{}

void Indie::Components::MoveComponent::setUp(bool value)
{
    this->up = value;
}

void Indie::Components::MoveComponent::setDown(bool value)
{
    this->down = value;
}

void Indie::Components::MoveComponent::setLeft(bool value)
{
    this->left = value;
}

void Indie::Components::MoveComponent::setRight(bool value)
{
    this->right = value;
}

void Indie::Components::MoveComponent::setDrop(bool value)
{
    this->drop = value;
}

bool Indie::Components::MoveComponent::getUp() const
{
    return this->up;
}

bool Indie::Components::MoveComponent::getDown() const
{
    return this->down;
}

bool Indie::Components::MoveComponent::getLeft() const
{
    return this->left;
}

bool Indie::Components::MoveComponent::getRight() const
{
    return this->right;
}

bool Indie::Components::MoveComponent::getDrop() const
{
    return this->drop;
}
