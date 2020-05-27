/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** MapComponent
*/

#include "MapComponent.hpp"

Indie::Components::MapComponent::MapComponent(const irr::core::vector2di &dimension, Indie::Components::MAP_TYPE type, Indie::Components::THEME theme)
    : dimension(dimension), type(type), theme(theme), map(dimension.Y), mapState(MAP_STATE::DEFAULT)
{
    for (int i = 0 ; i < dimension.Y; i++)
        this->map[i].resize(dimension.X);
}

const Indie::Components::MAP_TYPE &Indie::Components::MapComponent::getType() const
{
    return this->type;
}

const Indie::Components::THEME &Indie::Components::MapComponent::getTheme() const
{
    return this->theme;
}

const irr::core::vector2di &Indie::Components::MapComponent::getDimension() const
{
    return this->dimension;
}

const std::vector<std::vector<Indie::Components::OBJECT>> &Indie::Components::MapComponent::getMap() const
{
    return this->map;
}

const Indie::Components::MAP_STATE &Indie::Components::MapComponent::getMapState() const
{
    return this->mapState;
}

void Indie::Components::MapComponent::setMapState(Indie::Components::MAP_STATE newState)
{
    this->mapState = newState;
}

void Indie::Components::MapComponent::setType(Indie::Components::MAP_TYPE type)
{
    this->type = type;
}

void Indie::Components::MapComponent::setTheme(Indie::Components::THEME theme)
{
    this->theme = theme;
}

void Indie::Components::MapComponent::setDimension(const irr::core::vector2di &dimension)
{
    this->dimension = dimension;
}

void Indie::Components::MapComponent::setMap(const std::vector<std::vector<Indie::Components::OBJECT>> &map)
{
    this->map = map;
}