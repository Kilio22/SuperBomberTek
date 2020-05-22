/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** MeshComponent
*/

#include "MeshComponent.hpp"
#include "Exceptions.h"

const std::string Indie::Components::MeshComponent::STAND_MESH_PATH = "../ressources/static_mesh/character/red.obj";
const std::string Indie::Components::MeshComponent::RUN_MESH_PATH = "../ressources/animated_mesh/character/untitled_walk.b3d";

Indie::Components::MeshComponent::MeshComponent(const ContextManager &contextManager, const std::string &texturePath)
{
    irr::scene::IAnimatedMesh *newMesh = contextManager.getSceneManager()->getMesh(STAND_MESH_PATH.c_str());
    irr::video::ITexture *newTexture = contextManager.getDriver()->getTexture(texturePath.c_str());

    if (newMesh == nullptr) {
        throw Indie::Exceptions::FileNotFoundException("HitboxComponent::HitboxComponent", "Cannot found file: ");
    }
    if (newTexture == nullptr) {
        throw Indie::Exceptions::FileNotFoundException("HitboxComponent::HitboxComponent", "Cannot found file: " + texturePath);
    }
    this->texture = newTexture;
    this->meshs.insert({STAND, newMesh});
    newMesh = contextManager.getSceneManager()->getMesh(RUN_MESH_PATH.c_str());
    if (newMesh == nullptr) {
        throw Indie::Exceptions::FileNotFoundException("HitboxComponent::HitboxComponent", "Cannot found file: ");
    }
    this->meshs.insert({RUN, newMesh});
    this->currentPosition = STAND;
}

irr::video::ITexture *Indie::Components::MeshComponent::getTexture() const
{
    return this->texture;
}

const Indie::Components::MeshComponent::POSITION &Indie::Components::MeshComponent::getCurrentPosition() const
{
    return this->currentPosition;
}

void Indie::Components::MeshComponent::setCurrentPosition(POSITION newPostition)
{
    this->currentPosition = newPostition;
}

irr::scene::IAnimatedMesh *Indie::Components::MeshComponent::getMeshByPosition(POSITION pos) const
{
    auto found = this->meshs.find(pos);

    if (found == this->meshs.end())
        return nullptr;
    return found->second;
}
