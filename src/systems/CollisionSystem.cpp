/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** CollisionSystem
*/

#include "CollisionSystem.hpp"
#include "Components.h"

bool Indie::Systems::CollisionSystem::checkCollisionWithWalls(EntityManager &entityManager, const irr::core::aabbox3df &characterBoundingBox) const
{
    for (auto wall : entityManager.each<Components::WallComponent, Components::RenderComponent, Components::PositionComponent>()) {
        Components::RenderComponent *wallRenderComponent = wall->getComponent<Components::RenderComponent>();

        if (characterBoundingBox.intersectsWithBox(wallRenderComponent->getMesh()->getTransformedBoundingBox()) == true) {
            return true;
        }
    }
    return false;
}

bool Indie::Systems::CollisionSystem::checkCollisionWithCharacters(EntityManager &entityManager, const irr::core::aabbox3df &characterBoundingBox, const irr::core::vector3df &currentCharacterPosition) const
{
    for (auto character : entityManager.each<Components::MoveComponent, Components::VelocityComponent, Components::PositionComponent, Components::HitboxComponent>()) {
        Components::HitboxComponent *characterHitBoxComponent = character->getComponent<Components::HitboxComponent>();
        if (characterHitBoxComponent->getMesh()->getPosition() != currentCharacterPosition) {
            if (characterBoundingBox.intersectsWithBox(characterHitBoxComponent->getMesh()->getTransformedBoundingBox()) == true)
                return true;
        }
    }
    return false;
}

irr::core::aabbox3df Indie::Systems::CollisionSystem::updateCharacterBoundingBox(irr::core::aabbox3df characterBoundingBox, const irr::core::vector3df &currentPosition, const irr::core::vector3df &wantedPosition) const
{
    if (wantedPosition.X < currentPosition.X) {
        characterBoundingBox.MaxEdge.X -= currentPosition.X - wantedPosition.X;
        characterBoundingBox.MinEdge.X -= currentPosition.X - wantedPosition.X;
    } else {
        characterBoundingBox.MaxEdge.X += wantedPosition.X - currentPosition.X;
        characterBoundingBox.MinEdge.X += wantedPosition.X - currentPosition.X;
    }
    if (wantedPosition.Z < currentPosition.Z) {
        characterBoundingBox.MaxEdge.Z -= currentPosition.Z - wantedPosition.Z;
        characterBoundingBox.MinEdge.Z -= currentPosition.Z - wantedPosition.Z;
    } else {
        characterBoundingBox.MaxEdge.Z += wantedPosition.Z - currentPosition.Z;
        characterBoundingBox.MinEdge.Z += wantedPosition.Z - currentPosition.Z;
    }
    return characterBoundingBox;
}

void Indie::Systems::CollisionSystem::onUpdate(irr::f32 deltaTime, EntityManager &entityManager) const
{
    for (auto character : entityManager.each<Components::MoveComponent, Components::VelocityComponent, Components::PositionComponent, Components::HitboxComponent>()) {
        Components::HitboxComponent *characterHitBoxComponent = character->getComponent<Components::HitboxComponent>();
        Components::PositionComponent *characterPositionComponent = character->getComponent<Components::PositionComponent>();
        Components::VelocityComponent *characterVelocityComponent = character->getComponent<Components::VelocityComponent>();

        irr::core::vector3df currentPosition = characterHitBoxComponent->getMesh()->getPosition();
        irr::core::vector3df wantedPosition = characterPositionComponent->getPosition();

        if (currentPosition != wantedPosition) {
            irr::core::aabbox3df updatedBoundingBox = this->updateCharacterBoundingBox(
                characterHitBoxComponent->getMesh()->getTransformedBoundingBox(), currentPosition, wantedPosition);

            if (this->checkCollisionWithWalls(entityManager, updatedBoundingBox) == true) {
                characterPositionComponent->setPosition(currentPosition);
                characterVelocityComponent->setVelocity(0);
                continue;
            }
            if (this->checkCollisionWithCharacters(entityManager, updatedBoundingBox, currentPosition) == true) {
                characterPositionComponent->setPosition(currentPosition);
                characterVelocityComponent->setVelocity(0);
                continue;
            }
        }
    }
}
