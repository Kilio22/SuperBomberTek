/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** MeshSystem
*/

#include "MeshSystem.hpp"
#include "Components.h"
#include "Exceptions.h"

void Indie::Systems::MeshSystem::changeMesh(const ContextManager &contextManager, Indie::Components::RenderComponent *renderComp,
    irr::scene::IAnimatedMesh *mesh, irr::video::ITexture *texture) const
{
    irr::scene::IAnimatedMeshSceneNode *newMeshNode
        = contextManager.getSceneManager()->addAnimatedMeshSceneNode(mesh, renderComp->getMesh()->getParent());

    newMeshNode->setMaterialFlag(irr::video::EMF_LIGHTING, true);
    newMeshNode->setMaterialFlag(irr::video::EMF_FOG_ENABLE, true);
    newMeshNode->setMaterialTexture(0, texture);
    newMeshNode->setVisible(true);
    renderComp->setMesh(newMeshNode);
}

void Indie::Systems::MeshSystem::onUpdate(irr::f32, EntityManager &entityManager) const
{
    auto &contextManager = ServiceLocator::getInstance().get<ContextManager>();

    for (auto entity :
        entityManager.each<Indie::Components::MeshComponent, Indie::Components::VelocityComponent, Indie::Components::RenderComponent>()) {
        Components::VelocityComponent *velComponent = entity->getComponent<Indie::Components::VelocityComponent>();
        Components::MeshComponent *meshComponent = entity->getComponent<Indie::Components::MeshComponent>();
        Components::RenderComponent *renderComponent = entity->getComponent<Indie::Components::RenderComponent>();

        if (entity->has<Indie::Components::TimerComponent>() == true) {
            if ((int)meshComponent->getCurrentMeshState() != (int)Indie::Components::MeshComponent::MESH_STATE::DIE) {
                this->changeMesh(contextManager, renderComponent, meshComponent->getMeshByState(Indie::Components::MeshComponent::MESH_STATE::DIE),
                    meshComponent->getTexture());
                meshComponent->setCurrentMeshState(Indie::Components::MeshComponent::MESH_STATE::DIE);
            }
            continue;
        }
        if (velComponent->getVelocity() != 0 && meshComponent->getCurrentMeshState() != Indie::Components::MeshComponent::MESH_STATE::RUN) {
            this->changeMesh(contextManager, renderComponent, meshComponent->getMeshByState(Indie::Components::MeshComponent::MESH_STATE::RUN),
                meshComponent->getTexture());
            meshComponent->setCurrentMeshState(Indie::Components::MeshComponent::MESH_STATE::RUN);
        } else if (velComponent->getVelocity() == 0 && meshComponent->getCurrentMeshState() != Indie::Components::MeshComponent::MESH_STATE::STAND) {
            this->changeMesh(contextManager, renderComponent, meshComponent->getMeshByState(Indie::Components::MeshComponent::MESH_STATE::STAND),
                meshComponent->getTexture());
            meshComponent->setCurrentMeshState(Indie::Components::MeshComponent::MESH_STATE::STAND);
        }
    }
}
