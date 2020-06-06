/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** EntityBuilder
*/

#ifndef ENTITYBUILDER_HPP_
#define ENTITYBUILDER_HPP_

#include "Components.h"
#include "ContextManager.hpp"
#include "EntityManager.hpp"

namespace Indie
{
    /**
     * @brief The EntityBuilder class
     */
    class EntityBuilder
    {
    public:
        EntityBuilder();
        ~EntityBuilder() = default;

        /**
         * @brief Creates a ground entity
         *
         * @param position The position of the ground
         * @param modelPath The model of the ground
         * @param texturePath The texture of the ground
         * @return Entity* The new ground entity
         */
        Entity *createGround(const irr::core::vector3df &position, const std::string &modelPath, const std::string &texturePath);

        /**
         * @brief Creates a player entity
         *
         * @param position The position of the player
         * @param modelPath The model of the player
         * @param texturePath The texture of the player
         * @param keys The keys of the player
         * @param playerName The name of the player
         * @param playerColor The color of the player
         * @param startPosition Where the player starts in the map
         * @return Entity* The new player entity
         */
        Entity *createPlayer(const irr::core::vector3df &position, const std::string &modelPath, const std::string &texturePath, std::unordered_map<irr::EKEY_CODE, Components::KEY_TYPE> keys, const std::string &playerName, Components::PlayerComponent::PLAYER_COLOR playerColor, Components::PlayerComponent::PLAYER_START_POSITION startPosition);

        /**
         * @brief Creates a AI entity
         *
         * @param position The position of the AI
         * @param modelPath The model of the AI
         * @param texturePath The texture of the AI
         * @param playerNb The name of the AI
         * @param playerColor The color of the AI
         * @param startPosition Where the AI starts in the map
         * @return Entity* The new AI entity
         */
        Entity *createAi(const irr::core::vector3df &position, const std::string &modelPath, const std::string &texturePath, const std::string &playerName, Components::PlayerComponent::PLAYER_COLOR playerColor, Components::PlayerComponent::PLAYER_START_POSITION startPosition);

        /**
         * @brief Creates a Wall entity
         *
         * @param position The position of the wall
         * @param modelPath The model of the wall
         * @param texturePath The texture of the wall
         * @param canBeDestroyed The wall is a solid of destructible one
         * @return Entity* The new wall entity
         */
        Entity *createWall(const irr::core::vector3df &position, const std::string &modelPath, const std::string &texturePath, bool canBeDestroyed);

        /**
         * @brief Creates a Bomb entity
         *
         * @param position The position of the bomb
         * @param modelPath The model of the bomb
         * @param texturePath The texture of the bomb
         * @param idOwner The owner id
         * @param range The range of the bomb
         * @return Entity* The new bomb entity
         */
        Entity *createBomb(const irr::core::vector3df &position, const std::string &modelPath, const std::string &texturePath, int idOwner, unsigned int range);

        /**
         * @brief Creates a new Map entity
         *
         * @param dimension Dimensions of the map
         * @param type Type of the map
         * @param theme Theme of the map
         * @param mapPath The path of the map (not mandatory)
         * @return Entity* The new map entity
         */
        Entity *createMap(const irr::core::vector2di &dimension, const Indie::Components::MAP_TYPE &type, const Indie::Components::THEME &theme, const std::string &mapPath = "");

        /**
         * @brief Creates a new Lava entity
         *
         * @param position The position of the lava
         * @param modelPath The model of the lava
         * @param texturePath The texture of the lava
         * @param angle The angle of the lava
         * @param ownerId The owner id
         * @return Entity* The new lava entity
         */
        Entity *createLava(const irr::core::vector3df &position, const std::string &modelPath, const std::string &texturePath, float angle, int ownerId);

        /**
         * @brief Creates a new power up entity
         *
         * @param position The position of the power up
         * @param modelPath The model of the power up
         * @param texturePath The texture of the power up
         * @param type The type of the power up
         * @return Entity* The new power up entity
         */
        Entity *createPowerUp(irr::core::vector3df position, const std::string &modelPath, const std::string &texturePath, Components::POWERUP_TYPE type);

        /**
         * @brief Creates a new power down entity
         *
         * @param position The position of the power down
         * @param modelPath The model of the power down
         * @param texturePath The texture of the power down
         * @param type The type of the power down
         * @return Entity* The new power pown
         */
        Entity *createPowerDown(irr::core::vector3df position, const std::string &modelPath, const std::string &texturePath, Components::POWERDOWN_TYPE type);

        /**
         * @brief Creates a Shake entity
         * @return Entity* The new shake entity
         */
        Entity *createShake(void);

    private:
        EntityManager &entityManager;
        ContextManager &contextManager;
    };
}

#endif /* !ENTITYBUILDER_HPP_ */
