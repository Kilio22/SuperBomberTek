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
#include "ServiceLocator.hpp"

namespace Indie::Components
{
    class AIComponent
    {
        public:
            AIComponent() = default;
            ~AIComponent() = default;
            
            enum Direction {
                UP = 0,
                RIGHT = 1,
                DOWN = 2,
                LEFT = 3,
                NONE = 5 
            };
            std::vector<std::vector<int>> getMap() const;

            void pathFinder(std::vector<std::vector<int>> &map, int initX, int initY, int value);
            void findPosition(std::vector<std::vector<int>> map, int initX, int initY, std::array<int, 3> &position /*std::vector<std::array<int, 3>> banned_position*/);

            void getShortlessPath(std::vector<std::vector<int>> &map, int initX, int initY, int futurX, int futurY);

            void setNextDirection(std::vector<std::vector<int>> &map, int posX, int posY);
            irr::core::vector3df getNextPosition(int posX, int posY);
            void setDirection(enum Direction direction);
            enum Direction getDirection() const;

            int getNextXDirection() const;
            int getNextYDirection() const;

            bool hasArrived(std::vector<std::vector<int>> &map) const;
            bool isMoving(enum Direction direction);
            bool hasMoved(irr::core::vector3df position, irr::core::vector3df nextPosition);

            int setZone(std::vector<std::vector<int>> &map, int initX, int initY, int value);
            int getZone();
        protected:
        private:
            int _nextX = -1;
            int _nextY = -1;
            int _endX = -1;
            int _endY = -1;
            enum Direction _direction = NONE;
            int _dangerZone = 0;
    };
}

#endif /* !AICOMPONENT_HPP_ */