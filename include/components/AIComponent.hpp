/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** AIComponent
*/

#ifndef AICOMPONENT_HPP_
#define AICOMPONENT_HPP_

#include "MapComponent.hpp"
#include <irrlicht.h>
#include <vector>

namespace Indie::Components
{
    enum class DIRECTION
    {
        LEFT,
        RIGHT,
        UP,
        DOWN,
        NONE
    };

    enum class ACTION
    {
        GO_BOX,
        GO_SAFE,
        FIND_BOX,
        PLACE_BOMB,
        BOMB_PLACED,
        DODGE,
        STANDBY
    };

    /**
     * @brief AI Component
     */
    class AIComponent
    {
    public:
        AIComponent() = default;
        ~AIComponent() = default;

        /**
         * @brief Checks if the ai has moved to the next position (in center of the case)
         * @return true Ai has move
         * @return false Ai hasn't move yet
         */
        bool hasMoved(irr::core::vector3df position, irr::core::vector3df nextPosition, AIComponent *ai) const;

        /**
         * @brief Sets the nextDirection
         * @param map The pathfinding map with the shortless path
         * @param acPos Actual position of AI
         */
        void setNextDirection(std::vector<std::vector<OBJECT>> &map, irr::core::vector2di acPos);

        /**
         * @brief Sets the direction of AI
         * @param direction Enum Direction: All direction actions for the AI
         */
        void setDirection(DIRECTION direction);

        /**
         * @brief Sets the action of AI
         * @param action Enum Action: All possible actions for the AI
         */
        void setAction(ACTION action);

        /**
         * @brief Sets behavior of AI, the behvior depends ont the number of enemies in the same area with the AI
         * @param value The behavior value
         */
        void setBehavior(unsigned int value);

        /**
         * @brief Gets the behavior value of AI
         * @return The behavior value
         */
        unsigned int getBehavior() const;

        /**
         * @brief Gets the actual direction of the AI
         * @return The direction value
         */
        DIRECTION getDirection() const;

        /**
         * @brief Gets the actual action of AI
         * @return The action value
         */
        ACTION getAction() const;

        /**
         * @brief Gets the next postion of AI
         * @return The vector of the nextPosition
         */
        irr::core::vector2di getNextPosition() const;

    private:
        int nextPosX = 0;
        int nextPosY = 0;
        unsigned int behavior = 0;
        DIRECTION direction = DIRECTION::NONE;
        ACTION action = ACTION::STANDBY;
    };
}

#endif /* !AICOMPONENT_HPP_ */