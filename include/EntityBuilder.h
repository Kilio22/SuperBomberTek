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
private:

public:
    EntityBuilder() = delete;
    EntityBuilder(const EntityBuilder &) = delete;
    void operator=(const EntityBuilder &) = delete;
    ~EntityBuilder();

    static Entity *createGround(EntityManager &entityManager,
        irr::core::vector3df const &vector, const std::string &modelPath,
        const std::string &texturePath, ContextManager &contextManager)
    {
        Entity *entity = entityManager.createEntity();

        entity->addComponent<Components::PositionComponent>(
            vector.X, vector.Y, vector.Z);
        entity->addComponent<Components::RenderComponent>(
            modelPath, texturePath, contextManager);
        return entity;
    }

    static Entity *createPlayer(EntityManager &entityManager)
    {
        Entity *entity = entityManager.createEntity();

        return entity;
    }
};

}

#endif /* !ENTITYBUILDER_HPP_ */
