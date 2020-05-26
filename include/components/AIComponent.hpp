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
        STANDBY
    };
    class AIComponent
    {
        public:
            AIComponent() = default;
            ~AIComponent() = default;

            void setPathFinding(std::vector<std::vector<OBJECT>> &map, irr::core::vector2di aiPosition, int value);

            void findPosition(std::vector<std::vector<OBJECT>> &map, std::array<int, 3> &position /*std::vector<std::array<int, 3>> banned_position*/);

            void getShortlessPath(std::vector<std::vector<OBJECT>> &map, irr::core::vector2di acPos, irr::core::vector2di nextPos);

            void setNextDirection(std::vector<std::vector<OBJECT>> &map, int posX, int posY);

            void setDirection(DIRECTION direction);
            DIRECTION getDirection() const;

            int getNextXDirection() const;
            int getNextYDirection() const;

            bool hasArrived(std::vector<std::vector<OBJECT>> &map) const;
            bool isMoving(DIRECTION direction);
            bool hasMoved(irr::core::vector3df position, irr::core::vector3df nextPosition);

            int setZone(std::vector<std::vector<OBJECT>> &map, int initX, int initY, int value);
            int getZone();

        private:
            int _nextX = 0;
            int _nextY = 0;
            int _endX = 0;
            int _endY = 0;
            DIRECTION _direction = DIRECTION::NONE;
            int _dangerZone = 0;
    };
}

#endif /* !AICOMPONENT_HPP_ */