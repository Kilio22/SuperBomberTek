/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** RenderComponent
*/

#include <iostream>
#include "RenderComponent.hpp"

Indie::Components::RenderComponent::RenderComponent(std::string const &modelPath, std::string const &texturePath, irr::scene::ISceneManager *sceneManager, irr::video::IVideoDriver *driver)
    : AComponent(0)
{
    irr::scene::IAnimatedMesh *newMesh = sceneManager->getMesh(modelPath.c_str());
    irr::video::ITexture *newTexture = driver->getTexture(texturePath.c_str());

    if (newMesh == nullptr || newTexture == nullptr) {
        // TODO: throw exception
    }
    this->mesh = sceneManager->addAnimatedMeshSceneNode(newMesh, 0);
    this->mesh->setMaterialFlag(irr::video::EMF_LIGHTING, false);
    this->mesh->setMaterialTexture(0, newTexture);
    this->mesh->setMD2Animation(irr::scene::EMAT_STAND);
}

Indie::Components::RenderComponent::~RenderComponent()
{
    this->mesh->remove();
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