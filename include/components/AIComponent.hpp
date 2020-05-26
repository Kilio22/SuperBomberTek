/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** AIComponent
*/

#ifndef AICOMPONENT_HPP_
#define AICOMPONENT_HPP_

#include <array>
#include <vector>
#include <irrlicht.h>
#include "MapComponent.hpp"
#include "ServiceLocator.hpp"

namespace Indie::Components
{
    enum class DIRECTION {
        LEFT,
        RIGHT,
        UP,
        DOWN,
        NONE,
    };

    enum class ACTION {
        GO_BOX,
        GO_PLAYER,
        PLACE_BOMB,
        BOMB_PLACED,
        STANDBY
    };

    class AIComponent
    {
        public:
            AIComponent() = default;
            ~AIComponent() = default;

            void setNextDirection(std::vector<std::vector<OBJECT>> &map, irr::core::vector2di acPos);
            void setDirection(DIRECTION direction);
            void setAction(ACTION action);

            DIRECTION getDirection() const;
            ACTION getAction() const;

            irr::core::vector2di getNextPosition() const;
        private:
            int nextPosX = 0;
            int nextPosY = 0;
            DIRECTION direction = DIRECTION::NONE;
            ACTION action = ACTION::STANDBY;
    };
}

#endif /* !AICOMPONENT_HPP_ */