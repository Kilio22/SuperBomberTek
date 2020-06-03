/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** EntityBuilder
*/

#include "EntityBuilder.hpp"

Indie::EntityBuilder::EntityBuilder()
    : entityManager(ServiceLocator::getInstance().get<EntityManager>())
    , contextManager(ServiceLocator::getInstance().get<ContextManager>())
{
}

Indie::Entity *Indie::EntityBuilder::createGround(const irr::core::vector3df &position, const std::string &modelPath, const std::string &texturePath)
{
    Entity *entity = this->entityManager.createEntity();

    entity->addComponent<PositionComponent>(position.X, position.Y, position.Z);
    entity->addComponent<RenderComponent>(modelPath, texturePath, this->contextManager, position, true);
    return entity;
}

Indie::Entity *Indie::EntityBuilder::createPlayer(const irr::core::vector3df &position, const std::string &modelPath, const std::string &texturePath,
    std::map<irr::EKEY_CODE, KEY_TYPE> keys, const std::string &playerName, PlayerComponent::PLAYER_COLOR playerColor,
    PlayerComponent::PLAYER_START_POSITION startPosition)
{
    Entity *entity = this->entityManager.createEntity();

    entity->addComponent<PositionComponent>(position.X, position.Y, position.Z);
    entity->addComponent<RenderComponent>(modelPath, texturePath, this->contextManager, position, true);
    entity->addComponent<HitboxComponent>(position, this->contextManager);
    entity->addComponent<InputComponent>(keys);
    entity->addComponent<MoveComponent>();
    entity->addComponent<VelocityComponent>();
    entity->addComponent<MeshComponent>(this->contextManager, texturePath);
    entity->addComponent<RotationComponent>();
    entity->addComponent<PlayerComponent>(playerName, playerColor, startPosition);
    return entity;
}

Indie::Entity *Indie::EntityBuilder::createAi(const irr::core::vector3df &position, const std::string &modelPath, const std::string &texturePath,
    const std::string &playerName, PlayerComponent::PLAYER_COLOR playerColor, PlayerComponent::PLAYER_START_POSITION startPosition)
{
    Entity *entity = this->entityManager.createEntity();

    entity->addComponent<PositionComponent>(position.X, position.Y, position.Z);
    entity->addComponent<RenderComponent>(modelPath, texturePath, this->contextManager, position, true);
    entity->addComponent<HitboxComponent>(position, this->contextManager);
    entity->addComponent<AIComponent>();
    entity->addComponent<MoveComponent>();
    entity->addComponent<VelocityComponent>();
    entity->addComponent<MeshComponent>(contextManager, texturePath);
    entity->addComponent<RotationComponent>();
    entity->addComponent<PlayerComponent>(playerName, playerColor, startPosition);
    entity->addComponent<PathFinderComponent>();
    return entity;
}

Indie::Entity *Indie::EntityBuilder::createWall(
    const irr::core::vector3df &position, const std::string &modelPath, const std::string &texturePath, bool canBeDestroyed)
{
    Entity *entity = this->entityManager.createEntity();

    entity->addComponent<PositionComponent>(position.X, position.Y, position.Z);
    entity->addComponent<RenderComponent>(modelPath, texturePath, this->contextManager, position, true);
    entity->addComponent<WallComponent>(canBeDestroyed);
    return entity;
}

Indie::Entity *Indie::EntityBuilder::createBomb(
    const irr::core::vector3df &position, const std::string &modelPath, const std::string &texturePath, int idOwner, unsigned int range)
{
    Entity *entity = this->entityManager.createEntity();

    entity->addComponent<PositionComponent>(position.X, position.Y, position.Z);
    entity->addComponent<RenderComponent>(modelPath, texturePath, this->contextManager, position, true);
    entity->addComponent<BombComponent>(idOwner, range);
    entity->addComponent<TimerComponent>(3.f);
    return entity;
}

Indie::Entity *Indie::EntityBuilder::createMap(
    const irr::core::vector2di &dimension, const Indie::Components::MAP_TYPE &type, const Indie::Components::THEME &theme, const std::string &mapPath)
{
    return this->entityManager.createUniqueEntity<MapComponent>(dimension, type, theme, mapPath);
}

Indie::Entity *Indie::EntityBuilder::createLava(
    const irr::core::vector3df &position, const std::string &modelPath, const std::string &texturePath, float angle, int ownerId)
{
    Entity *entity = this->entityManager.createEntity();

    entity->addComponent<PositionComponent>(position.X, position.Y, position.Z);
    entity->addComponent<RenderComponent>(modelPath, texturePath, this->contextManager, position, true);
    entity->addComponent<RotationComponent>(angle);
    entity->addComponent<TimerComponent>(.75f);
    entity->addComponent<KillComponent>(ownerId);
    return entity;
}

Indie::Entity *Indie::EntityBuilder::createPowerUp(
    irr::core::vector3df position, const std::string &modelPath, const std::string &texturePath, Components::POWERUP_TYPE type)
{
    Entity *entity = this->entityManager.createEntity();

    position.Z -= 10;
    entity->addComponent<PositionComponent>(position.X, position.Y, position.Z);
    entity->addComponent<RenderComponent>(modelPath, texturePath, this->contextManager, position, false);
    entity->addComponent<RotationComponent>(0.f, 50.f);
    entity->addComponent<PowerUpComponent>(type);
    return entity;
}

Indie::Entity *Indie::EntityBuilder::createPowerDown(
    irr::core::vector3df position, const std::string &modelPath, const std::string &texturePath, Components::POWERDOWN_TYPE type)
{
    Entity *entity = this->entityManager.createEntity();

    position.Z -= 10;
    entity->addComponent<PositionComponent>(position.X, position.Y, position.Z);
    entity->addComponent<RenderComponent>(modelPath, texturePath, this->contextManager, position, false);
    entity->addComponent<RotationComponent>(0.f, 50.f);
    entity->addComponent<PowerDownComponent>(type);
    return entity;
}

Indie::Entity *Indie::EntityBuilder::createShake(void)
{
    return this->entityManager.createUniqueEntity<ShakeComponent>();
}
