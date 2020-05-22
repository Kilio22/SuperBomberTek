/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** MeshSystem
*/

#include "MeshSystem.hpp"
#include "Exceptions.h"
#include "Components.h"

void Indie::Systems::MeshSystem::changeMesh(const ContextManager &contextManager, Indie::Components::RenderComponent *renderComp, const std::string &meshPath, const std::string &texturePath) const
{
    irr::scene::IAnimatedMesh *newMesh = contextManager.getSceneManager()->getMesh(meshPath.c_str());
    irr::video::ITexture *newTexture = contextManager.getDriver()->getTexture(texturePath.c_str());

    if (newMesh == nullptr) {
        throw Indie::Exceptions::FileNotFoundException("HitboxComponent::HitboxComponent", "Cannot found file: " + meshPath);
    }
    if (newTexture == nullptr) {
        throw Indie::Exceptions::FileNotFoundException("HitboxComponent::HitboxComponent", "Cannot found file: " + texturePath);
    }
    irr::scene::IAnimatedMeshSceneNode *newMeshNode = contextManager.getSceneManager()->addAnimatedMeshSceneNode(newMesh, renderComp->getMesh()->getParent());
    newMeshNode->setMaterialFlag(irr::video::EMF_LIGHTING, true);
    newMeshNode->setMaterialFlag(irr::video::EMF_FOG_ENABLE, true);
    newMeshNode->setMaterialTexture(0, newTexture);
    newMeshNode->setVisible(true);
    renderComp->setMesh(newMeshNode);
}

void Indie::Systems::MeshSystem::onUpdate(int ticks, EntityManager &entityManager, const ContextManager &contextManager) const
{
    for (auto entity : entityManager.each<Indie::Components::MeshComponent, Indie::Components::VelocityComponent, Indie::Components::RenderComponent>()) {
        auto velComponent = entity->getComponent<Indie::Components::VelocityComponent>();
        auto meshComponent = entity->getComponent<Indie::Components::MeshComponent>();
        auto renderComponent = entity->getComponent<Indie::Components::RenderComponent>();

        if (velComponent->getVelocity() != 0 && meshComponent->getCurrentPosition() != Indie::Components::MeshComponent::RUN) {
            this->changeMesh(contextManager, renderComponent, meshComponent->getMeshPathByPosition(Indie::Components::MeshComponent::RUN), meshComponent->getTexturePath());
            meshComponent->setCurrentPosition(Indie::Components::MeshComponent::RUN);
        } else if (velComponent->getVelocity() == 0 && meshComponent->getCurrentPosition() != Indie::Components::MeshComponent::STAND) {
            this->changeMesh(contextManager, renderComponent, meshComponent->getMeshPathByPosition(Indie::Components::MeshComponent::STAND), meshComponent->getTexturePath());
            meshComponent->setCurrentPosition(Indie::Components::MeshComponent::STAND);
        }
    }
}
