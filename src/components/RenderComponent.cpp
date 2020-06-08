/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** RenderComponent
*/

#include <iostream>
#include "RenderComponent.hpp"
#include "Exceptions.h"

Indie::Components::RenderComponent::RenderComponent(std::string const &meshPath, std::string const &texturePath, const ContextManager &contextManager, irr::core::vector3df position, bool lightSensible)
    : meshPath(meshPath), texturePath(texturePath)
{
    irr::scene::IAnimatedMesh *newMesh = contextManager.getSceneManager()->getMesh(meshPath.c_str());
    irr::video::ITexture *newTexture = contextManager.getDriver()->getTexture(texturePath.c_str());

    if (newMesh == nullptr) {
        throw Indie::Exceptions::FileNotFoundException(ERROR_STR, "Cannot found file: " + meshPath);
    }
    if (newTexture == nullptr) {
        throw Indie::Exceptions::FileNotFoundException(ERROR_STR, "Cannot found file: " + texturePath);
    }
    this->mesh = contextManager.getSceneManager()->addAnimatedMeshSceneNode(newMesh, 0);
    if (this->mesh == nullptr) {
        throw Indie::Exceptions::DeviceException(ERROR_STR, "Cannot add animatedMeshSceneNode");
    }
    this->mesh->setMaterialFlag(irr::video::EMF_LIGHTING, lightSensible);
    this->mesh->setMaterialFlag(irr::video::EMF_FOG_ENABLE, true);
    this->mesh->setMaterialTexture(0, newTexture);
    this->mesh->setVisible(true);
    this->mesh->setPosition(position);
    this->texture = newTexture;
}

Indie::Components::RenderComponent::~RenderComponent()
{
    this->mesh->remove();
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

irr::video::ITexture *Indie::Components::RenderComponent::getTexture(void) const
{
    return this->texture;
}

const std::string &Indie::Components::RenderComponent::getMeshPath(void) const
{
    return this->meshPath;
}

const std::string &Indie::Components::RenderComponent::getTexturePath(void) const
{
    return this->texturePath;
}