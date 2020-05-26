/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** PathFinderComponent
*/

#ifndef PATHFINDERCOMPONENT_HPP_
#define PATHFINDERCOMPONENT_HPP_

#include <array>
#include <vector>
#include <irrlicht.h>
#include "MapComponent.hpp"
#include "ServiceLocator.hpp"

namespace Indie::Components
{
    class PathFinderComponent {
        public:
            PathFinderComponent() = default;
            ~PathFinderComponent() = default;

            void setPathFinding(irr::core::vector2di aiPosition, int value);
            void findPosition(std::array<int, 3> &position);
            void getShortlessPath(irr::core::vector2di acPos, irr::core::vector2di nextPos);

            irr::core::vector2di getEndPosition() const;
            std::vector<std::vector<Indie::Components::OBJECT>> getMap() const;

            void setMap(std::vector<std::vector<OBJECT>> map);

        private:
            std::vector<std::vector<OBJECT>> map;
            int endPosX = 0;
            int endPosY = 0;
    };
}

#endif /* !PATHFINDERCOMPONENT_HPP_ */