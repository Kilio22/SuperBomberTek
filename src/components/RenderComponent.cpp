/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** RenderComponent
*/

#include <iostream>
#include "RenderComponent.hpp"
#include "Exceptions.h"

Indie::Components::RenderComponent::RenderComponent(std::string const &meshPath, std::string const &texturePath, const ContextManager &contextManager, irr::core::vector3df position)
{
    irr::scene::IAnimatedMesh *newMesh = contextManager.getSceneManager()->getMesh(meshPath.c_str());
    irr::video::ITexture *newTexture = contextManager.getDriver()->getTexture(texturePath.c_str());

    if (newMesh == nullptr) {
        throw Indie::Exceptions::FileNotFoundException("HitboxComponent::HitboxComponent", "Cannot found file: " + meshPath);
    }
    if (newTexture == nullptr) {
        throw Indie::Exceptions::FileNotFoundException("HitboxComponent::HitboxComponent", "Cannot found file: " + texturePath);
    }
    this->mesh = contextManager.getSceneManager()->addAnimatedMeshSceneNode(newMesh, 0);
    this->mesh->setMaterialFlag(irr::video::EMF_LIGHTING, true);
    this->mesh->setMaterialFlag(irr::video::EMF_FOG_ENABLE, true);
    this->mesh->setMaterialTexture(0, newTexture);
    this->mesh->setVisible(true);
    this->mesh->setPosition(position);
}

irr::scene::IAnimatedMeshSceneNode *Indie::Components::RenderComponent::getMesh() const
{
    return this->mesh;
}

void Indie::Components::RenderComponent::setMesh(irr::scene::IAnimatedMeshSceneNode *newMesh)
{
    if (!newMesh) {
        return;
    }
    this->mesh->remove();
    this->mesh = newMesh;
}
