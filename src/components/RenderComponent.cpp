/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** RenderComponent
*/

#include <iostream>
#include "RenderComponent.hpp"

Indie::Components::RenderComponent::RenderComponent(std::string const &modelPath, std::string const &texturePath, ContextManager const &contextManager)
{
    irr::scene::IAnimatedMesh *newMesh = contextManager.getSceneManager()->getMesh(modelPath.c_str());
    irr::video::ITexture *newTexture = contextManager.getDriver()->getTexture(texturePath.c_str());

    if (newMesh == nullptr || newTexture == nullptr) {
        // TODO: throw exception
    }
    this->mesh = contextManager.getSceneManager()->addAnimatedMeshSceneNode(newMesh, 0);
    this->mesh->setMaterialFlag(irr::video::EMF_LIGHTING, true);
    this->mesh->setMaterialFlag(irr::video::EMF_FOG_ENABLE, true);
    this->mesh->setMaterialTexture(0, newTexture);
    this->mesh->setVisible(true);
}

Indie::Components::RenderComponent::~RenderComponent()
{
}

irr::scene::IAnimatedMeshSceneNode *Indie::Components::RenderComponent::getMesh()
{
    return this->mesh;
}

void Indie::Components::RenderComponent::setMesh(irr::scene::IAnimatedMesh *newMesh, irr::scene::ISceneManager *sceneManager)
{
    irr::scene::ISceneNode *parent = this->mesh->getParent();

    if (!newMesh) {
        return;
    }
    this->mesh->remove();
    this->mesh = sceneManager->addAnimatedMeshSceneNode(newMesh, parent);
}