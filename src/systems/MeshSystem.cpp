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
            if ((int)meshComponent->getCurrentPosition() != (int)Indie::Components::MeshComponent::POSITION::DIE) {
                this->changeMesh(contextManager, renderComponent, meshComponent->getMeshByPosition(Indie::Components::MeshComponent::POSITION::DIE),
                    meshComponent->getTexture());
                meshComponent->setCurrentPosition(Indie::Components::MeshComponent::POSITION::DIE);
            }
            continue;
        }
        if (velComponent->getVelocity() != 0 && meshComponent->getCurrentPosition() != Indie::Components::MeshComponent::POSITION::RUN) {
            this->changeMesh(contextManager, renderComponent, meshComponent->getMeshByPosition(Indie::Components::MeshComponent::POSITION::RUN),
                meshComponent->getTexture());
            meshComponent->setCurrentPosition(Indie::Components::MeshComponent::POSITION::RUN);
        } else if (velComponent->getVelocity() == 0 && meshComponent->getCurrentPosition() != Indie::Components::MeshComponent::POSITION::STAND) {
            this->changeMesh(contextManager, renderComponent, meshComponent->getMeshByPosition(Indie::Components::MeshComponent::POSITION::STAND),
                meshComponent->getTexture());
            meshComponent->setCurrentPosition(Indie::Components::MeshComponent::POSITION::STAND);
        }
    }
}
