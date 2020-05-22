/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** EntityBuilder
*/

#ifndef ENTITYBUILDER_HPP_
#define ENTITYBUILDER_HPP_

#include "Components.h"
#include "EntityManager.hpp"
#include <irrlicht.h>

namespace Indie {

class EntityBuilder {
    public:
        EntityBuilder() = delete;
        EntityBuilder(const EntityBuilder &) = delete;
        void operator=(const EntityBuilder &) = delete;
        ~EntityBuilder() = default;

        static Entity *createGround(EntityManager &entityManager,
            irr::core::vector3df const &vector, const std::string &modelPath,
            const std::string &texturePath, ContextManager &contextManager)
        {
            Entity *entity = entityManager.createEntity();

            entity->addComponent<Components::PositionComponent>(
                vector.X, vector.Y, vector.Z);
            entity->addComponent<Components::RenderComponent>(
                modelPath, texturePath, contextManager, vector);
            return entity;
        }

        static Entity *createPlayer(EntityManager &entityManager, const irr::core::vector3df &vector, const std::string &modelPath,
    const std::string &texturePath, ContextManager &contextManager, std::map<irr::EKEY_CODE, Components::KEY_TYPE> keys)
        {
            Entity *entity = entityManager.createEntity();

            entity->addComponent<Components::PositionComponent>(
                vector.X, vector.Y, vector.Z);
            entity->addComponent<Components::RenderComponent>(
                modelPath, texturePath, contextManager, vector);
            entity->addComponent<Components::HitboxComponent>(vector, contextManager);
            entity->addComponent<Components::InputComponent>(keys);
            entity->addComponent<Components::MoveComponent>();
            entity->addComponent<Components::VelocityComponent>();
            entity->addComponent<Components::MeshComponent>(contextManager, texturePath);
            entity->addComponent<Components::RotationComponent>();
            return entity;
        }

        static Entity *createWall(EntityManager &entityManager, const irr::core::vector3df &vector, const std::string &modelPath,
    const std::string &texturePath, ContextManager &contextManager, bool canBeDestroyed)
        {
            Entity *entity = entityManager.createEntity();

            entity->addComponent<Components::PositionComponent>(
                vector.X, vector.Y, vector.Z);
            entity->addComponent<Components::RenderComponent>(
                modelPath, texturePath, contextManager, vector);
            entity->addComponent<Components::WallComponent>(canBeDestroyed);
            return entity;
        }
    };
}

#endif /* !ENTITYBUILDER_HPP_ */
