/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** CollisionSystem
*/

#include "CollisionSystem.hpp"
#include "Components.h"

void Indie::Systems::CollisionSystem::onUpdate(irr::f32 deltaTime, EntityManager &entityManager, const ContextManager &) const
{
    for (auto character : entityManager.each<Components::MoveComponent, Components::VelocityComponent, Components::PositionComponent, Components::HitboxComponent>()) {
        Components::HitboxComponent *characterHitBoxComponent = character->getComponent<Components::HitboxComponent>();
        Components::PositionComponent *characterPositionComponent = character->getComponent<Components::PositionComponent>();
        Components::VelocityComponent *characterVelocityComponent = character->getComponent<Components::VelocityComponent>();

        irr::core::vector3df currentPosition = characterHitBoxComponent->getMesh()->getPosition();
        irr::core::vector3df wantedPosition = characterPositionComponent->getPosition();

        if (currentPosition != wantedPosition) {
            irr::core::aabbox3df boundingBox = characterHitBoxComponent->getMesh()->getTransformedBoundingBox();

            if (wantedPosition.X < currentPosition.X) {
                boundingBox.MaxEdge.X -= currentPosition.X - wantedPosition.X;
                boundingBox.MinEdge.X -= currentPosition.X - wantedPosition.X;
            } else {
                boundingBox.MaxEdge.X += wantedPosition.X - currentPosition.X;
                boundingBox.MinEdge.X += wantedPosition.X - currentPosition.X;
            }
            if (wantedPosition.Z < currentPosition.Z) {
                boundingBox.MaxEdge.Z -= currentPosition.Z - wantedPosition.Z;
                boundingBox.MinEdge.Z -= currentPosition.Z - wantedPosition.Z;
            } else {
                boundingBox.MaxEdge.Z += wantedPosition.Z - currentPosition.Z;
                boundingBox.MinEdge.Z += wantedPosition.Z - currentPosition.Z;
            }
            for (auto wall : entityManager.each<Components::WallComponent, Components::RenderComponent, Components::PositionComponent>()) {
                Components::RenderComponent *wallRenderComponent = wall->getComponent<Components::RenderComponent>();
                if (boundingBox.intersectsWithBox(wallRenderComponent->getMesh()->getTransformedBoundingBox()) == true) {
                    characterPositionComponent->setPosition(currentPosition);
                    characterVelocityComponent->setVelocity(0);
                    break;
                }
            }
        }
    }
}
