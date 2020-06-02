/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** CollisionSystem
*/

#include "CollisionSystem.hpp"

Indie::Components::POWERUP_TYPE Indie::Systems::CollisionSystem::checkCollisionWithPowerUp(
    EntityManager &entityManager, const irr::core::aabbox3df &characterBoundingBox) const
{
    for (auto powerUp : entityManager.each<Components::RenderComponent, Components::PowerUpComponent>()) {
        Components::PowerUpComponent *powerUpComponent = powerUp->getComponent<Components::PowerUpComponent>();
        Components::RenderComponent *renderComponent = powerUp->getComponent<Components::RenderComponent>();

        if (renderComponent->getMesh()->getTransformedBoundingBox().intersectsWithBox(characterBoundingBox) == true) {
            powerUp->needDestroy();
            return powerUpComponent->getType();
        }
    }
    return Components::POWERUP_TYPE::NONE;
}

void Indie::Systems::CollisionSystem::checkCollisionWithPowerUps(
    EntityManager &entityManager, const irr::core::aabbox3df &characterBoundingBox, Components::PlayerComponent *playerComponent) const
{
    Components::POWERUP_TYPE powerUpType = this->checkCollisionWithPowerUp(entityManager, characterBoundingBox);

    if (powerUpType == Components::POWERUP_TYPE::NONE)
        return;
    playerComponent->setXpCount(playerComponent->getXpCount() + 15);
    if (powerUpType == Components::POWERUP_TYPE::BOMB_UP) {
        playerComponent->setMaxBombNb(playerComponent->getMaxBombNb() + 1);
        playerComponent->setCurrentBombNb(playerComponent->getCurrentBombNb() + 1);
        return;
    }
    if (powerUpType == Components::POWERUP_TYPE::FIRE_UP) {
        playerComponent->setBombsRange(playerComponent->getBombsRange() + 1);
        return;
    }
    if (powerUpType == Components::POWERUP_TYPE::SPEED_UP) {
        playerComponent->setVelocityLevel(playerComponent->getVelocityLevel() + 1);
        return;
    }
    if (powerUpType == Components::POWERUP_TYPE::WALL_PASS) {
        playerComponent->setWallPass(true);
        return;
    }
}

bool Indie::Systems::CollisionSystem::checkCollisionWithCharacters(
    EntityManager &entityManager, const irr::core::aabbox3df &characterBoundingBox, const irr::core::vector3df &currentCharacterPosition) const
{
    for (auto character :
        entityManager.each<Components::MoveComponent, Components::VelocityComponent, Components::PositionComponent, Components::HitboxComponent>()) {
        Components::HitboxComponent *characterHitBoxComponent = character->getComponent<Components::HitboxComponent>();

        if (characterHitBoxComponent->getMesh()->getPosition() != currentCharacterPosition) {
            if (characterBoundingBox.intersectsWithBox(characterHitBoxComponent->getMesh()->getTransformedBoundingBox()) == true)
                return true;
        }
    }
    return false;
}

bool Indie::Systems::CollisionSystem::checkCollisionWithBombs(
    EntityManager &entityManager, const irr::core::aabbox3df &characterBoundingBox, int characterId) const
{
    for (auto bomb : entityManager.each<Components::BombComponent, Components::RenderComponent>()) {
        Components::RenderComponent *renderComponent = bomb->getComponent<Components::RenderComponent>();
        Components::BombComponent *bombComponent = bomb->getComponent<Components::BombComponent>();

        if (characterBoundingBox.intersectsWithBox(renderComponent->getMesh()->getTransformedBoundingBox()) == true
            && bombComponent->getIdOwner() != characterId) {
            return true;
        }
    }
    return false;
}

bool Indie::Systems::CollisionSystem::checkCollisionWithWalls(
    EntityManager &entityManager, const irr::core::aabbox3df &characterBoundingBox, Components::PlayerComponent *playerComponent) const
{
    bool ret_val = false;

    for (Entity *entity : entityManager.each<Components::WallComponent, Components::RenderComponent, Components::PositionComponent>()) {
        Components::RenderComponent *renderComponent = entity->getComponent<Components::RenderComponent>();
        Components::WallComponent *wallComponent = entity->getComponent<Components::WallComponent>();

        if (characterBoundingBox.intersectsWithBox(renderComponent->getMesh()->getTransformedBoundingBox()) == true) {
            if (wallComponent->getCanBeDestroyed() == true && playerComponent->getWallPass() == true && ret_val != true) {
                continue;
            }
            ret_val = true;
        }
    }
    return ret_val;
}

std::pair<bool, int> Indie::Systems::CollisionSystem::checkCollisionWithKillingEntities(
    EntityManager &entityManager, const irr::core::aabbox3df &characterBoundingBox, Components::PlayerComponent *playerComponent) const
{
    for (Entity *entity : entityManager.each<Components::RenderComponent, Components::KillComponent>()) {
        auto renderComponent = entity->getComponent<Components::RenderComponent>();
        auto killComponent = entity->getComponent<Components::KillComponent>();

        if (characterBoundingBox.intersectsWithBox(renderComponent->getMesh()->getTransformedBoundingBox()) == true) {
            return { true, killComponent->getOwnerId() };
        }
    }
    return { false, -1 };
}

irr::core::aabbox3df Indie::Systems::CollisionSystem::updateCharacterBoundingBox(
    irr::core::aabbox3df characterBoundingBox, const irr::core::vector3df &currentPosition, const irr::core::vector3df &wantedPosition) const
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
    for (auto character :
        entityManager
            .each<Components::VelocityComponent, Components::PositionComponent, Components::HitboxComponent, Components::PlayerComponent>()) {
        Components::HitboxComponent *characterHitBoxComponent = character->getComponent<Components::HitboxComponent>();
        Components::PositionComponent *characterPositionComponent = character->getComponent<Components::PositionComponent>();
        Components::VelocityComponent *characterVelocityComponent = character->getComponent<Components::VelocityComponent>();
        Components::PlayerComponent *characterPlayerComponent = character->getComponent<Components::PlayerComponent>();

        irr::core::vector3df currentPosition = characterHitBoxComponent->getMesh()->getPosition();
        irr::core::vector3df wantedPosition = characterPositionComponent->getPosition();
        irr::core::aabbox3df updatedBoundingBox = characterHitBoxComponent->getMesh()->getTransformedBoundingBox();

        if (character->has<Components::TimerComponent>() == true)
            continue;
        if (currentPosition != wantedPosition) {
            updatedBoundingBox = this->updateCharacterBoundingBox(updatedBoundingBox, currentPosition, wantedPosition);

            this->checkCollisionWithPowerUps(entityManager, updatedBoundingBox, characterPlayerComponent);
            auto [collides, colliderOwnerId] = this->checkCollisionWithKillingEntities(entityManager, updatedBoundingBox, characterPlayerComponent);
            if (collides == true) {
                auto colliderPlayerEntity = entityManager.getById(colliderOwnerId);
                auto colliderPlayerComponent
                    = colliderPlayerEntity == nullptr ? nullptr : colliderPlayerEntity->getComponent<Components::PlayerComponent>();

                if (colliderPlayerComponent != nullptr && colliderPlayerEntity != character)
                    colliderPlayerComponent->setXpCount(colliderPlayerComponent->getXpCount() + 100);
                character->addComponent<Components::TimerComponent>(1.75f);
                characterPlayerComponent->setIsDead(true);
                characterVelocityComponent->setVelocity(0);
                characterPositionComponent->setPosition(currentPosition);
                continue;
            }
            if (this->checkCollisionWithWalls(entityManager, updatedBoundingBox, characterPlayerComponent) == true) {
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
        }
        auto [collides, colliderOwnerId] = this->checkCollisionWithKillingEntities(entityManager, updatedBoundingBox, characterPlayerComponent);
        if (collides == true) {
            auto colliderPlayerEntity = entityManager.getById(colliderOwnerId);
            auto colliderPlayerComponent
                = colliderPlayerEntity == nullptr ? nullptr : colliderPlayerEntity->getComponent<Components::PlayerComponent>();

            if (colliderPlayerComponent != nullptr && colliderPlayerEntity != character)
                colliderPlayerComponent->setXpCount(colliderPlayerComponent->getXpCount() + 100);
            character->addComponent<Components::TimerComponent>(1.75f);
            characterPlayerComponent->setIsDead(true);
        }
    }
}
