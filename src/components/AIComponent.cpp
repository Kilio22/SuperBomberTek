/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** AIComponent
*/

#include "AIComponent.hpp"
#include <iostream>

bool Indie::Components::AIComponent::hasMoved(irr::core::vector3df position, irr::core::vector3df nextPosition, AIComponent *ai) const
{
    if (ai->getDirection() == DIRECTION::UP && position.Z < nextPosition.Z)
        return false;
    if (ai->getDirection() == DIRECTION::DOWN && position.Z > nextPosition.Z)
        return false;
    if (ai->getDirection() == DIRECTION::RIGHT && position.X < nextPosition.X)
        return false;
    if (ai->getDirection() == DIRECTION::LEFT && position.X > nextPosition.X)
        return false;
    return true;
}

void Indie::Components::AIComponent::setNextDirection(std::vector<std::vector<OBJECT>> &map, irr::core::vector2di acPos)
{
    nextPosX = acPos.X;
    nextPosY = acPos.Y;

    map.at(acPos.Y).at(acPos.X) = static_cast<OBJECT>(0);
    if (map.at(acPos.Y + 1).at(acPos.X) == static_cast<OBJECT>(-99)) {
        setDirection(Indie::Components::DIRECTION::UP);
        nextPosY += 1;
        return;
    }
    if (map.at(acPos.Y).at(acPos.X + 1) == static_cast<OBJECT>(-99)) {
        setDirection(Indie::Components::DIRECTION::RIGHT);
        nextPosX += 1;
        return;
    }
    if (map.at(acPos.Y - 1).at(acPos.X) == static_cast<OBJECT>(-99)) {
        setDirection(Indie::Components::DIRECTION::DOWN);
        nextPosY -= 1;
        return;
    }
    if (map.at(acPos.Y).at(acPos.X - 1) == static_cast<OBJECT>(-99)) {
        setDirection(Indie::Components::DIRECTION::LEFT);
        nextPosX -= 1;
        return;
    }
}

void Indie::Components::AIComponent::forceNextDirection(irr::core::vector2di nextPos)
{
    this->nextPosX = nextPos.X;
    this->nextPosY = nextPos.Y;
}

void Indie::Components::AIComponent::setDirection(Indie::Components::DIRECTION direction)
{
    this->direction = direction;
}

void Indie::Components::AIComponent::setAction(Indie::Components::ACTION action)
{
    this->action = action;
}

Indie::Components::DIRECTION Indie::Components::AIComponent::getDirection() const
{
    return this->direction;
}

Indie::Components::ACTION Indie::Components::AIComponent::getAction() const
{
    return this->action;
}

irr::core::vector2di Indie::Components::AIComponent::getNextPosition() const
{
    return irr::core::vector2di(nextPosX, nextPosY);
}

void Indie::Components::AIComponent::setBehavior(unsigned int value)
{
    this->behavior = value;
}

unsigned int Indie::Components::AIComponent::getBehavior() const
{
    return this->behavior;
}