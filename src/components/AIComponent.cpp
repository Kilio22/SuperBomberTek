/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** AIComponent
*/

#include "AIComponent.hpp"
#include <iostream>


void Indie::Components::AIComponent::setNextDirection(std::vector<std::vector<OBJECT>> &map, irr::core::vector2di acPos)
{
    nextPosX = acPos.X;
    nextPosY = acPos.Y;

    std::cout << acPos.X << " " << acPos.Y << std::endl;

    map[acPos.Y][acPos.X] = static_cast<OBJECT>(0);
    if (map[acPos.Y - 1][acPos.X] == static_cast<OBJECT>(-99)) {
        setDirection(Indie::Components::DIRECTION::UP);
        nextPosY -= 1;
        return;
    }
    if (map[acPos.Y][acPos.X + 1] == static_cast<OBJECT>(-99)) {
        setDirection(Indie::Components::DIRECTION::RIGHT);
        nextPosX += 1;
        return;
    }
    if (map[acPos.Y + 1][acPos.X] == static_cast<OBJECT>(-99)) {
        setDirection(Indie::Components::DIRECTION::DOWN);
        nextPosY += 1;
        return;
    }
    if (map[acPos.Y][acPos.X - 1] == static_cast<OBJECT>(-99)) {
        setDirection(Indie::Components::DIRECTION::LEFT);
        std::cout << (int)getDirection() << std::endl;
        nextPosX -= 1;
        return;
    }
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