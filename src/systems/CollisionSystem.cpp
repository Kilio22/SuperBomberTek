/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** CollisionSystem
*/

#include "CollisionSystem.hpp"
#include "Components.h"

void Indie::Systems::CollisionSystem::onUpdate(int ticks, EntityManager &entityManager) const
{
    for (auto character : entityManager.each<Components::MoveComponent, Components::VelocityComponent, Components::PositionComponent>()) {
        Components::RenderComponent *characterRenderComponent = character->getComponent<Components::RenderComponent>();
        Components::PositionComponent *characterPositionComponent = character->getComponent<Components::PositionComponent>();
        irr::core::vector3df currentMeshPosition = characterRenderComponent->getMesh()->getPosition();
        irr::core::vector3df wantedPosition = characterPositionComponent->getPosition();
        if (currentMeshPosition != wantedPosition) {
            irr::core::aabbox3df currentBoundingBox = characterRenderComponent->getMesh()->getTransformedBoundingBox();

            if (wantedPosition.X < currentMeshPosition.X) {
                currentBoundingBox.MaxEdge.X -= 2;
                currentBoundingBox.MinEdge.X -= 2;
            } else {
                currentBoundingBox.MaxEdge.X += 2;
                currentBoundingBox.MinEdge.X += 2;
            }
            if (wantedPosition.Z < currentMeshPosition.Z) {
                currentBoundingBox.MaxEdge.Z -= 2;
                currentBoundingBox.MinEdge.Z -= 2;
            } else {
                currentBoundingBox.MaxEdge.Z += 2;
                currentBoundingBox.MinEdge.Z += 2;
            }
            std::cout << "before maxEdge x: " << characterRenderComponent->getMesh()->getTransformedBoundingBox().MaxEdge.X << std::endl;
            std::cout << "before maxEdge y: " << characterRenderComponent->getMesh()->getTransformedBoundingBox().MaxEdge.Y << std::endl;
            std::cout << "before maxEdge z: " << characterRenderComponent->getMesh()->getTransformedBoundingBox().MaxEdge.Z << std::endl;
            std::cout << "before MinEdge x: " << characterRenderComponent->getMesh()->getTransformedBoundingBox().MinEdge.X << std::endl;
            std::cout << "before MinEdge y: " << characterRenderComponent->getMesh()->getTransformedBoundingBox().MinEdge.Y << std::endl;
            std::cout << "before MinEdge z: " << characterRenderComponent->getMesh()->getTransformedBoundingBox().MinEdge.Z << std::endl;
            for (auto wall : entityManager.each<Components::WallComponent, Components::RenderComponent, Components::PositionComponent>()) {
                Components::RenderComponent *wallRenderComponent = wall->getComponent<Components::RenderComponent>();
                if (currentBoundingBox.intersectsWithBox(wallRenderComponent->getMesh()->getTransformedBoundingBox()) == true) {
                    characterPositionComponent->setPosition(currentMeshPosition);
                    break;
                }
            }
        }
    }
}
