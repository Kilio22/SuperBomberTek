/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** RenderSystem
*/

#include "RenderSystem.hpp"
#include "Components.h"

void Indie::Systems::RenderSystem::onUpdate(irr::f32, EntityManager &entityManager) const
{
    for (auto entity : entityManager.each<Components::RenderComponent, Components::PositionComponent>()) {
        auto renderComponent = entity->getComponent<Components::RenderComponent>();
        auto positionComponent = entity->getComponent<Components::PositionComponent>();
        auto hitBoxComponent = entity->getComponent<Components::HitboxComponent>();

        renderComponent->getMesh()->setPosition(positionComponent->getPosition());
        if (hitBoxComponent != nullptr) {
            hitBoxComponent->getMesh()->setPosition(positionComponent->getPosition());
        }
    }
    for (auto entity : entityManager.each<Components::RenderComponent, Components::RotationComponent>()) {
        auto renderComponent = entity->getComponent<Components::RenderComponent>();
        auto rotationComponent = entity->getComponent<Components::RotationComponent>();

        renderComponent->getMesh()->setRotation(rotationComponent->getAngle());
    }
}
