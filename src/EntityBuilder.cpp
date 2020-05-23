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
    return entity;
}

Indie::Entity *Indie::EntityBuilder::createAi(
    const irr::core::vector3df &vector, const std::string &modelPath,
    const std::string &texturePath)
{
    Entity *entity = this->entityManager.createEntity();

    entity->addComponent<Components::PositionComponent>(vector.X, vector.Y, vector.Z);
    entity->addComponent<Components::RenderComponent>(modelPath, texturePath, this->contextManager, vector);
    entity->addComponent<Components::HitboxComponent>(vector, this->contextManager);
    entity->addComponent<Components::AIComponent>();
    entity->addComponent<Components::MoveComponent>();
    entity->addComponent<Components::VelocityComponent>();
    entity->addComponent<Components::MeshComponent>(contextManager, texturePath);
    entity->addComponent<Components::RotationComponent>();
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
