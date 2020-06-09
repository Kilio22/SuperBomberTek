/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** CollisionSystem
*/

#include "CollisionSystem.hpp"
#include "SoundManager.hpp"

void Indie::Systems::CollisionSystem::checkCollisionWithPowerDowns(
    EntityManager &entityManager, const irr::core::aabbox3df &characterBoundingBox, Components::PlayerComponent *playerComponent) const
{
    Indie::Components::PowerDownComponent *powerDownComponent
        = this->checkCollisionWithEffect<Components::PowerDownComponent>(entityManager, characterBoundingBox);

    if (powerDownComponent == nullptr)
        return;
    ServiceLocator::getInstance().get<SoundManager>().playSound("power_down", characterBoundingBox.getCenter().X, characterBoundingBox.getCenter().Y, characterBoundingBox.getCenter().Z);
    playerComponent->setScore(playerComponent->getScore() - 10);
    if (powerDownComponent->getType() == Components::POWERDOWN_TYPE::BOMB_DOWN && playerComponent->getMaxBombNb() > 1) {
        playerComponent->setMaxBombNb(playerComponent->getMaxBombNb() - 1);
        if (playerComponent->getCurrentBombNb() > playerComponent->getMaxBombNb())
            playerComponent->setCurrentBombNb(playerComponent->getCurrentBombNb() - 1);
        return;
    }
    if (powerDownComponent->getType() == Components::POWERDOWN_TYPE::FIRE_DOWN && playerComponent->getBombsRange() > 2) {
        playerComponent->setBombsRange(playerComponent->getBombsRange() - 1);
        return;
    }
    if (powerDownComponent->getType() == Components::POWERDOWN_TYPE::SPEED_DOWN && playerComponent->getVelocityLevel() > 1) {
        playerComponent->setVelocityLevel(playerComponent->getVelocityLevel() - 1);
        return;
    }
}

void Indie::Systems::CollisionSystem::checkCollisionWithPowerUps(
    EntityManager &entityManager, const irr::core::aabbox3df &characterBoundingBox, Components::PlayerComponent *playerComponent) const
{
    Indie::Components::PowerUpComponent *powerUpComponent
        = this->checkCollisionWithEffect<Components::PowerUpComponent>(entityManager, characterBoundingBox);

    if (powerUpComponent == nullptr)
        return;
    ServiceLocator::getInstance().get<SoundManager>().playSound("power_up", characterBoundingBox.getCenter().X, characterBoundingBox.getCenter().Y, characterBoundingBox.getCenter().Z);
    playerComponent->setScore(playerComponent->getScore() + 15);
    if (powerUpComponent->getType() == Components::POWERUP_TYPE::BOMB_UP) {
        playerComponent->setMaxBombNb(playerComponent->getMaxBombNb() + 1);
        playerComponent->setCurrentBombNb(playerComponent->getCurrentBombNb() + 1);
        return;
    }
    if (powerUpComponent->getType() == Components::POWERUP_TYPE::FIRE_UP) {
        playerComponent->setBombsRange(playerComponent->getBombsRange() + 1);
        return;
    }
    if (powerUpComponent->getType() == Components::POWERUP_TYPE::SPEED_UP) {
        playerComponent->setVelocityLevel(playerComponent->getVelocityLevel() + 1);
        return;
    }
    if (powerUpComponent->getType() == Components::POWERUP_TYPE::WALL_PASS) {
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
    EntityManager &entityManager, const irr::core::aabbox3df &characterBoundingBox) const
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
    for (auto entity :
        entityManager
            .each<Components::VelocityComponent, Components::PositionComponent, Components::HitboxComponent, Components::PlayerComponent>()) {
        Components::HitboxComponent *entityHitBoxComponent = entity->getComponent<Components::HitboxComponent>();
        Components::PositionComponent *entityPositionComponent = entity->getComponent<Components::PositionComponent>();
        Components::VelocityComponent *entityVelocityComponent = entity->getComponent<Components::VelocityComponent>();
        Components::PlayerComponent *entityPlayerComponent = entity->getComponent<Components::PlayerComponent>();

        irr::core::vector3df currentPosition = entityHitBoxComponent->getMesh()->getPosition();
        irr::core::vector3df wantedPosition = entityPositionComponent->getPosition();
        irr::core::aabbox3df updatedBoundingBox = entityHitBoxComponent->getMesh()->getTransformedBoundingBox();

        if (entity->has<Components::TimerComponent>() == true)
            continue;
        if (currentPosition != wantedPosition) {
            updatedBoundingBox = this->updateCharacterBoundingBox(updatedBoundingBox, currentPosition, wantedPosition);

            this->checkCollisionWithPowerUps(entityManager, updatedBoundingBox, entityPlayerComponent);
            this->checkCollisionWithPowerDowns(entityManager, updatedBoundingBox, entityPlayerComponent);
            auto [collides, colliderOwnerId] = this->checkCollisionWithKillingEntities(entityManager, updatedBoundingBox);
            if (collides == true) {
                auto colliderPlayerEntity = entityManager.getById(colliderOwnerId);
                auto colliderPlayerComponent
                    = colliderPlayerEntity == nullptr ? nullptr : colliderPlayerEntity->getComponent<Components::PlayerComponent>();

                if (colliderPlayerComponent != nullptr && colliderPlayerEntity != entity) {
                    colliderPlayerComponent->setXpCount(colliderPlayerComponent->getXp() + 100);
                    colliderPlayerComponent->setScore(colliderPlayerComponent->getScore() + 100);
                }
                entity->addComponent<Components::TimerComponent>(1.75f);
                ServiceLocator::getInstance().get<SoundManager>().playSound("die", currentPosition.X, currentPosition.Y, currentPosition.Z);
                entityPlayerComponent->setIsDead(true);
                entityVelocityComponent->setVelocity(0);
                entityPositionComponent->setPosition(currentPosition);
                continue;
            }
            if (this->checkCollisionWithWalls(entityManager, updatedBoundingBox, entityPlayerComponent) == true) {
                entityPositionComponent->setPosition(currentPosition);
                entityVelocityComponent->setVelocity(0);
                continue;
            }
            if (this->checkCollisionWithCharacters(entityManager, updatedBoundingBox, currentPosition) == true) {
                entityPositionComponent->setPosition(currentPosition);
                entityVelocityComponent->setVelocity(0);
                continue;
            }
            if (this->checkCollisionWithBombs(entityManager, updatedBoundingBox, entity->getId()) == true) {
                entityPositionComponent->setPosition(currentPosition);
                entityVelocityComponent->setVelocity(0);
                continue;
            }
        }
        auto [collides, colliderOwnerId] = this->checkCollisionWithKillingEntities(entityManager, updatedBoundingBox);
        if (collides == true) {
            auto colliderPlayerEntity = entityManager.getById(colliderOwnerId);
            auto colliderPlayerComponent
                = colliderPlayerEntity == nullptr ? nullptr : colliderPlayerEntity->getComponent<Components::PlayerComponent>();

            if (colliderPlayerComponent != nullptr && colliderPlayerEntity != entity) {
                colliderPlayerComponent->setXpCount(colliderPlayerComponent->getXp() + 100);
                colliderPlayerComponent->setScore(colliderPlayerComponent->getScore() + 100);
            }
            entity->addComponent<Components::TimerComponent>(1.75f);
            ServiceLocator::getInstance().get<SoundManager>().playSound("die", currentPosition.X, currentPosition.Y, currentPosition.Z);
            entityPlayerComponent->setIsDead(true);
        }
    }
}
