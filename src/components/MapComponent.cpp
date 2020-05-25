/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** MapComponent
*/

#include "MapComponent.hpp"

Indie::Components::MapComponent::MapComponent(const irr::core::vector2di &dimension, const Indie::Components::MAP_TYPE &type, const Indie::Components::THEME &theme)
    : type(type), theme(theme), dimension(dimension)
{
    std::vector<std::vector<Components::OBJECT>> matrix(dimension.Y);
    for (int i = 0 ; i < dimension.Y; i++)
        matrix[i].resize(dimension.X);
    this->map = matrix;
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

void Indie::Components::MapComponent::setType(Indie::Components::MAP_TYPE type)
{
    this->type = type;
}

void Indie::Components::MapComponent::setTheme(Indie::Components::THEME theme)
{
    this->theme = theme;
}

void Indie::Components::MapComponent::setDimension(irr::core::vector2di dimension)
{
    this->dimension = dimension;
}

void Indie::Components::MapComponent::setMap(std::vector<std::vector<Indie::Components::OBJECT>> map)
{
    this->map = map;
}