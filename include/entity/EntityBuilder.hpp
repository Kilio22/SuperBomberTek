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
#include "ServiceLocator.hpp"
#include <irrlicht.h>

namespace Indie {

using namespace Components;

    class EntityBuilder {
        public:
            EntityBuilder();
            ~EntityBuilder() = default;

            Entity *createGround(const irr::core::vector3df &vector, const std::string &modelPath, const std::string &texturePath);
            Entity *createPlayer(const irr::core::vector3df &vector, const std::string &modelPath, const std::string &texturePath, std::map<irr::EKEY_CODE, KEY_TYPE> keys);
            Entity *createAi(const irr::core::vector3df &vector, const std::string &modelPath, const std::string &texturePath);
            Entity *createWall(const irr::core::vector3df &vector, const std::string &modelPath, const std::string &texturePath, bool canBeDestroyed);
            Entity *createBomb(const irr::core::vector3df &vector, const std::string &modelPath, const std::string &texturePath);

        private:
            EntityManager &entityManager;
            ContextManager &contextManager;
    };
}

#endif /* !ENTITYBUILDER_HPP_ */
