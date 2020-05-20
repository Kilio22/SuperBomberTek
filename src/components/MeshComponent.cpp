/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** MeshComponent
*/

#include "MeshComponent.hpp"

const std::map<Indie::Components::MeshComponent::POSITION, std::string> Indie::Components::MeshComponent::meshPaths = {{STAND, "ressources/static_mesh/character/red.obj"}, {RUN, "ressources/animated_mesh/character/untitled_walk.b3d"}};

Indie::Components::MeshComponent::MeshComponent(const std::string &texturePath)
{
    this->texturePath = texturePath;
    this->currentPosition = STAND;
}

const std::string &Indie::Components::MeshComponent::getTexturePath()
{
    return this->texturePath;
}

void Indie::Components::MeshComponent::setTexturePath(const std::string &newPath)
{
    this->texturePath = newPath;
}

Indie::Components::MeshComponent::POSITION Indie::Components::MeshComponent::getCurrentPosition()
{
    return this->currentPosition;
}

void Indie::Components::MeshComponent::setCurrentPosition(POSITION newPostition)
{
    this->currentPosition = newPostition;
}

std::string Indie::Components::MeshComponent::getMeshPathByPosition(POSITION pos)
{
    auto found = this->meshPaths.find(pos);

    if (found == this->meshPaths.end())
        return "";
    return found->second;
}
