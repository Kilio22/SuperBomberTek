/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** RenderSystem
*/

#include "RenderSystem.hpp"
#include "Components.h"
#include "FileNotFoundException.hpp"

void Indie::Systems::RenderSystem::changeBox(Entity *wall, Components::MAP_STATE state) const
{
    auto &contextManager = ServiceLocator::getInstance().get<ContextManager>();
    auto renderComponent = wall->getComponent<Components::RenderComponent>();
    auto texture = renderComponent->getTexture();
    irr::scene::IAnimatedMesh *newMesh = contextManager.getSceneManager()->getMesh(renderComponent->getMeshPath().c_str());
    irr::scene::IAnimatedMeshSceneNode *newAnimatedMesh = nullptr;

    if (newMesh == nullptr) {
        throw Exceptions::FileNotFoundException("HitboxComponent::HitboxComponent", "Cannot found file: " + renderComponent->getMeshPath());
    }
    if (state == Components::MAP_STATE::TRANSPARENT) {
        newAnimatedMesh = contextManager.getSceneManager()->addAnimatedMeshSceneNode(newMesh, 0);
        contextManager.getSceneManager()->getMeshManipulator()->setVertexColorAlpha(newAnimatedMesh->getMesh()->getMesh(0), 150);
        newAnimatedMesh->setMaterialFlag(irr::video::EMF_LIGHTING, false);
        newAnimatedMesh->setMaterialFlag(irr::video::EMF_BACK_FACE_CULLING, false);
        newAnimatedMesh->setMaterialType(irr::video::EMT_TRANSPARENT_VERTEX_ALPHA);
    } else {
        newAnimatedMesh = contextManager.getSceneManager()->addAnimatedMeshSceneNode(newMesh, 0);
        newAnimatedMesh->setMaterialFlag(irr::video::EMF_LIGHTING, true);
        newAnimatedMesh->setMaterialFlag(irr::video::EMF_FOG_ENABLE, true);
    }
    newAnimatedMesh->setMaterialTexture(0, texture);
    newAnimatedMesh->setVisible(true);
    renderComponent->setMesh(newAnimatedMesh);
}

void Indie::Systems::RenderSystem::changeBoxes(EntityManager &entityManager, Components::MAP_STATE state) const
{
    for (auto wall : entityManager.each<Components::WallComponent, Components::RenderComponent>()) {
        auto wallComponent = wall->getComponent<Components::WallComponent>();

        if (wallComponent->getCanBeDestroyed() == false)
            continue;
        this->changeBox(wall, state);
    }
}

void Indie::Systems::RenderSystem::checkMapState(EntityManager &entityManager) const
{
    Components::MAP_STATE currentState = Components::MAP_STATE::DEFAULT;
    Components::MAP_STATE newMapState = Components::MAP_STATE::DEFAULT;

    for (auto map : entityManager.each<Components::MapComponent>()) {
        currentState = map->getComponent<Components::MapComponent>()->getMapState();
    }
    for (auto player : entityManager.each<Components::PlayerComponent>()) {
        auto playerComponent = player->getComponent<Components::PlayerComponent>();

        if (playerComponent->getWallPass() == true) {
            newMapState = Components::MAP_STATE::TRANSPARENT;
        }
    }
    if (newMapState != currentState) {
        this->changeBoxes(entityManager, newMapState);
        for (auto map : entityManager.each<Components::MapComponent>()) {
           map->getComponent<Components::MapComponent>()->setMapState(newMapState);
        }
    }
}

void Indie::Systems::RenderSystem::onUpdate(irr::f32, EntityManager &entityManager) const
{
    this->checkMapState(entityManager);
    for (auto entity : entityManager.each<Components::RenderComponent, Components::PositionComponent>()) {
        auto renderComponent = entity->getComponent<Components::RenderComponent>();
        auto positionComponent = entity->getComponent<Components::PositionComponent>();

        renderComponent->getMesh()->setPosition(positionComponent->getPosition());
        if (entity->has<Components::HitboxComponent>() == true) {
            auto hitBoxComponent = entity->getComponent<Components::HitboxComponent>();

            hitBoxComponent->getMesh()->setPosition(positionComponent->getPosition());
        }
    }
    for (auto entity : entityManager.each<Components::RenderComponent, Components::RotationComponent>()) {
        auto renderComponent = entity->getComponent<Components::RenderComponent>();
        auto rotationComponent = entity->getComponent<Components::RotationComponent>();

        renderComponent->getMesh()->setRotation(rotationComponent->getAngle());
    }
}
