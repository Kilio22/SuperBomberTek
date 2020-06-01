/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** PathFInderComponent
*/

#include "PathFinderComponent.hpp"

void Indie::Components::PathFinderComponent::setMap(std::vector<std::vector<OBJECT>> map)
{
    this->map = map;
}

std::vector<std::vector<Indie::Components::OBJECT>> Indie::Components::PathFinderComponent::getMap() const
{
    return this->map;
}

void Indie::Components::PathFinderComponent::setMapBomb(std::vector<std::vector<OBJECT>> map)
{
    this->mapBomb = map;
}

std::vector<std::vector<Indie::Components::OBJECT>> Indie::Components::PathFinderComponent::getMapBomb() const
{
    return this->mapBomb;
}

void Indie::Components::PathFinderComponent::setEndMapPos(irr::core::vector2di endPos)
{
    this->endMapPos = endPos;
}

irr::core::vector2di Indie::Components::PathFinderComponent::getEndMapPos() const
{
    return this->endMapPos;
}
