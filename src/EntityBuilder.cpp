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

Indie::Entity *Indie::EntityBuilder::createGround(
    const irr::core::vector3df &vector, const std::string &modelPath,
    const std::string &texturePath)
{
    Entity *entity = this->entityManager.createEntity();

    entity->addComponent<PositionComponent>(vector.X, vector.Y, vector.Z);
    entity->addComponent<RenderComponent>(modelPath, texturePath, this->contextManager, vector);
    return entity;
}

Indie::Entity *Indie::EntityBuilder::createPlayer(
    const irr::core::vector3df &vector, const std::string &modelPath,
    const std::string &texturePath, std::map<irr::EKEY_CODE, KEY_TYPE> keys)
{
    Entity *entity = this->entityManager.createEntity();

    entity->addComponent<PositionComponent>(vector.X, vector.Y, vector.Z);
    entity->addComponent<RenderComponent>(modelPath, texturePath, this->contextManager, vector);
    entity->addComponent<HitboxComponent>(vector, this->contextManager);
    entity->addComponent<InputComponent>(keys);
    entity->addComponent<MoveComponent>();
    entity->addComponent<VelocityComponent>();
    entity->addComponent<MeshComponent>(this->contextManager, texturePath);
    entity->addComponent<RotationComponent>();
    entity->addComponent<PlayerComponent>();
    return entity;
}

Indie::Entity *Indie::EntityBuilder::createAi(
    const irr::core::vector3df &vector, const std::string &modelPath,
    const std::string &texturePath)
{
    Entity *entity = this->entityManager.createEntity();

    entity->addComponent<PositionComponent>(vector.X, vector.Y, vector.Z);
    entity->addComponent<RenderComponent>(modelPath, texturePath, this->contextManager, vector);
    entity->addComponent<HitboxComponent>(vector, this->contextManager);
    entity->addComponent<AIComponent>();
    entity->addComponent<MoveComponent>();
    entity->addComponent<VelocityComponent>();
    entity->addComponent<MeshComponent>(contextManager, texturePath);
    entity->addComponent<RotationComponent>();
    entity->addComponent<PlayerComponent>();
    return entity;
}

Indie::Entity *Indie::EntityBuilder::createWall(
    const irr::core::vector3df &vector, const std::string &modelPath,
    const std::string &texturePath, bool canBeDestroyed)
{
    Entity *entity = this->entityManager.createEntity();

    entity->addComponent<PositionComponent>(vector.X, vector.Y, vector.Z);
    entity->addComponent<RenderComponent>(modelPath, texturePath, this->contextManager, vector);
    entity->addComponent<WallComponent>(canBeDestroyed);
    return entity;
}

Indie::Entity *Indie::EntityBuilder::createBomb(
    const irr::core::vector3df &vector, const std::string &modelPath,
    const std::string &texturePath)
{
    Entity *entity = this->entityManager.createEntity();

    entity->addComponent<PositionComponent>(vector.X, vector.Y, vector.Z);
    entity->addComponent<RenderComponent>(modelPath, texturePath, this->contextManager, vector);
    entity->addComponent<BombComponent>();
    return entity;
}

Indie::Entity *Indie::EntityBuilder::createMap(const irr::core::vector2di &dimension, const Indie::Components::MAP_TYPE &type, const Indie::Components::THEME &theme)
{
    Entity *entity = this->entityManager.createEntity();

    entity->addComponent<MapComponent>(dimension, type, theme);
    return entity;
}