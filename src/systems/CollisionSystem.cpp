/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** CollisionSystem
*/

#include "CollisionSystem.hpp"
#include "Components.h"

bool Indie::Systems::CollisionSystem::checkCollisionWithPowerUp(EntityManager &entityManager, const irr::core::aabbox3df &characterBoundingBox, Indie::Components::POWERUP_TYPE type) const
{
    for (auto powerUp : entityManager.each<Components::RenderComponent, Components::PowerUpComponent>()) {
        Components::PowerUpComponent *powerUpComponent = powerUp->getComponent<Components::PowerUpComponent>();

        if (powerUpComponent->getType() != type)
            continue;
        Components::RenderComponent *renderComponent = powerUp->getComponent<Components::RenderComponent>();
        if (renderComponent->getMesh()->getTransformedBoundingBox().intersectsWithBox(characterBoundingBox) == true) {
            powerUp->needDestroy();
            return true;
        }
    }
    return false;
}

void Indie::Systems::CollisionSystem::checkCollisionWithPowerUps(EntityManager &entityManager, const irr::core::aabbox3df &characterBoundingBox,
                                                                    Components::PlayerComponent *playerComponent) const
{
    if (this->checkCollisionWithPowerUp(entityManager, characterBoundingBox, Components::POWERUP_TYPE::BOMB_UP) == true) {
        playerComponent->setMaxBombNb(playerComponent->getMaxBombNb() + 1);
        playerComponent->setCurrentBombNb(playerComponent->getCurrentBombNb() + 1);
        return;
    }
    if (this->checkCollisionWithPowerUp(entityManager, characterBoundingBox, Components::POWERUP_TYPE::FIRE_UP) == true) {
        playerComponent->setBombsRange(playerComponent->getBombsRange() + 1);
        return;
    }
    if (this->checkCollisionWithPowerUp(entityManager, characterBoundingBox, Components::POWERUP_TYPE::SPEED_UP) == true) {
        playerComponent->setVelocity(playerComponent->getVelocity() + 5);
        return;
    }
    if (this->checkCollisionWithPowerUp(entityManager, characterBoundingBox, Components::POWERUP_TYPE::WALL_PASS) == true) {
        playerComponent->setWallPass(true);
        return;
    }
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

bool Indie::Systems::CollisionSystem::checkCollisionWithBombs(EntityManager &entityManager, const irr::core::aabbox3df &characterBoundingBox, int characterId) const
{
    for (auto bomb : entityManager.each<Components::BombComponent, Components::RenderComponent>()) {
        Components::RenderComponent *renderComponent = bomb->getComponent<Components::RenderComponent>();
        Components::BombComponent *bombComponent = bomb->getComponent<Components::BombComponent>();

        if (characterBoundingBox.intersectsWithBox(renderComponent->getMesh()->getTransformedBoundingBox()) == true && bombComponent->getIdOwner() != characterId) {
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

void Indie::Systems::CollisionSystem::onUpdate(irr::f32, EntityManager &entityManager) const
{
    for (auto character : entityManager.each<Components::VelocityComponent, Components::PositionComponent, Components::HitboxComponent, Components::PlayerComponent>()) {
        Components::HitboxComponent *characterHitBoxComponent = character->getComponent<Components::HitboxComponent>();
        Components::PositionComponent *characterPositionComponent = character->getComponent<Components::PositionComponent>();
        Components::VelocityComponent *characterVelocityComponent = character->getComponent<Components::VelocityComponent>();
        Components::PlayerComponent *characterPlayerComponent = character->getComponent<Components::PlayerComponent>();

        irr::core::vector3df currentPosition = characterHitBoxComponent->getMesh()->getPosition();
        irr::core::vector3df wantedPosition = characterPositionComponent->getPosition();

        if (currentPosition != wantedPosition && character->has<Components::TimerComponent>() == false) {
            irr::core::aabbox3df updatedBoundingBox = this->updateCharacterBoundingBox(
                characterHitBoxComponent->getMesh()->getTransformedBoundingBox(), currentPosition, wantedPosition);

            this->checkCollisionWithPowerUps(entityManager, updatedBoundingBox, characterPlayerComponent);
            if (this->checkCollisionWithEntities<Components::WallComponent, Components::RenderComponent, Components::PositionComponent>(entityManager, updatedBoundingBox) == true) {
                characterPositionComponent->setPosition(currentPosition);
                characterVelocityComponent->setVelocity(0);
                continue;
            }
            if (this->checkCollisionWithCharacters(entityManager, updatedBoundingBox, currentPosition) == true) {
                characterPositionComponent->setPosition(currentPosition);
                characterVelocityComponent->setVelocity(0);
                continue;
            }
            if (this->checkCollisionWithBombs(entityManager, updatedBoundingBox, character->getId()) == true) {
                characterPositionComponent->setPosition(currentPosition);
                characterVelocityComponent->setVelocity(0);
                continue;
            }
            if (this->checkCollisionWithEntities<Components::RenderComponent, Components::KillComponent>(entityManager, updatedBoundingBox) == true) {
                characterPositionComponent->setPosition(currentPosition);
                characterVelocityComponent->setVelocity(0);
                character->addComponent<Components::TimerComponent>(1.75f);
                continue;
            }
        }
        if (this->checkCollisionWithEntities<Components::RenderComponent, Components::KillComponent>(entityManager, characterHitBoxComponent->getMesh()->getTransformedBoundingBox()) == true) {
            characterPositionComponent->setPosition(currentPosition);
            characterVelocityComponent->setVelocity(0);
            character->addComponent<Components::TimerComponent>(1.75f);
        }
    }
}
