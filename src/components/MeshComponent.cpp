/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** MeshComponent
*/

#include "MeshComponent.hpp"
#include "Exceptions.h"

const std::string Indie::Components::MeshComponent::STAND_MESH_PATH = "../ressources/animated_mesh/character/character_idle.b3d";
const std::string Indie::Components::MeshComponent::RUN_MESH_PATH = "../ressources/animated_mesh/character/character_walk.b3d";
const std::string Indie::Components::MeshComponent::DIE_MESH_PATH = "../ressources/animated_mesh/character/character_die.b3d";

Indie::Components::MeshComponent::MeshComponent(const ContextManager &contextManager, const std::string &texturePath)
{
    irr::scene::IAnimatedMesh *newMesh = contextManager.getSceneManager()->getMesh(STAND_MESH_PATH.c_str());
    irr::video::ITexture *newTexture = contextManager.getDriver()->getTexture(texturePath.c_str());

    if (newMesh == nullptr) {
        throw Indie::Exceptions::FileNotFoundException(ERROR_STR, "Cannot found file: " + STAND_MESH_PATH);
    }
    if (newTexture == nullptr) {
        throw Indie::Exceptions::FileNotFoundException(ERROR_STR, "Cannot found file: " + texturePath);
    }
    this->texture = newTexture;
    this->meshs.insert({MESH_STATE::STAND, newMesh});
    newMesh = contextManager.getSceneManager()->getMesh(RUN_MESH_PATH.c_str());
    if (newMesh == nullptr) {
        throw Indie::Exceptions::FileNotFoundException(ERROR_STR, "Cannot found file: " + RUN_MESH_PATH);
    }
    this->meshs.insert({MESH_STATE::RUN, newMesh});
    newMesh = contextManager.getSceneManager()->getMesh(DIE_MESH_PATH.c_str());
    if (newMesh == nullptr) {
        throw Indie::Exceptions::FileNotFoundException(ERROR_STR, "Cannot found file: " + DIE_MESH_PATH);
    }
    this->meshs.insert({MESH_STATE::DIE, newMesh});
    this->currentMeshState = MESH_STATE::STAND;
}

irr::video::ITexture *Indie::Components::MeshComponent::getTexture() const
{
    return this->texture;
}

const Indie::Components::MeshComponent::MESH_STATE &Indie::Components::MeshComponent::getCurrentMeshState() const
{
    return this->currentMeshState;
}

void Indie::Components::MeshComponent::setCurrentMeshState(MESH_STATE newState)
{
    this->currentMeshState = newState;
}

irr::scene::IAnimatedMesh *Indie::Components::MeshComponent::getMeshByState(MESH_STATE state) const
{
    auto found = this->meshs.find(state);

    if (found == this->meshs.end())
        return nullptr;
    return found->second;
}
