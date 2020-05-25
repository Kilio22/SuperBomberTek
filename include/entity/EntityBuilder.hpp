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

            Entity *createGround(const irr::core::vector3df &position, const std::string &modelPath, const std::string &texturePath);
            Entity *createPlayer(const irr::core::vector3df &position, const std::string &modelPath, const std::string &texturePath, std::map<irr::EKEY_CODE, KEY_TYPE> keys);
            Entity *createAi(const irr::core::vector3df &position, const std::string &modelPath, const std::string &texturePath);
            Entity *createWall(const irr::core::vector3df &position, const std::string &modelPath, const std::string &texturePath, bool canBeDestroyed);
            Entity *createBomb(const irr::core::vector3df &position, const std::string &modelPath, const std::string &texturePath, int idOwner, u_int32_t range);
            Entity *createMap(const irr::core::vector2di &dimension, const Indie::Components::MAP_TYPE &type, const Indie::Components::THEME &theme);
            Entity *createLava(const irr::core::vector3df &position, const std::string &modelPath, const std::string &texturePath, float angle);
            Entity *createPowerUp(const irr::core::vector3df &position, const std::string &modelPath, const std::string &texturePath, Components::POWERUP_TYPE type);

        private:
            EntityManager &entityManager;
            ContextManager &contextManager;
    };
}

#endif /* !ENTITYBUILDER_HPP_ */
