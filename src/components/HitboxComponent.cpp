/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** HitboxComponent
*/

#include "HitboxComponent.hpp"
#include "Exceptions.h"
#include "ContextManager.hpp"

Indie::Components::HitboxComponent::HitboxComponent(irr::core::vector3df position, const ContextManager &contextManager)
{
    irr::scene::IAnimatedMesh *newMesh = contextManager.getSceneManager()->getMesh("../ressources/static_mesh/character/characterBox.b3d");

    if (newMesh == nullptr) {
        throw Indie::Exceptions::FileNotFoundException("HitboxComponent::HitboxComponent", "Cannot found file: ../ressources/static_mesh/character/characterBox.b3d");
    }
    contextManager.getSceneManager()->getMeshManipulator()->setVertexColors(newMesh, irr::video::SColor(0, 20, 20, 20));
    this->mesh = contextManager.getSceneManager()->addAnimatedMeshSceneNode(newMesh, 0);
    this->mesh->setMaterialFlag(irr::video::EMF_LIGHTING, false);
    this->mesh->setMaterialFlag(irr::video::EMF_BACK_FACE_CULLING, false);
    this->mesh->setMaterialType(irr::video::EMT_TRANSPARENT_VERTEX_ALPHA);
    this->mesh->setVisible(true);
    this->mesh->setPosition(position);
}

irr::scene::IAnimatedMeshSceneNode *Indie::Components::HitboxComponent::getMesh() const
{
    return this->mesh;
}
