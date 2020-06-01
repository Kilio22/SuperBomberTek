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

            void setMap(std::vector<std::vector<OBJECT>> map);
            void setMapBomb(std::vector<std::vector<OBJECT>> map);
            void setEndMapPos(irr::core::vector2di endPos);

            std::vector<std::vector<OBJECT>> getMap() const;

            std::vector<std::vector<OBJECT>> getMapBomb() const;
            irr::core::vector2di getEndMapPos() const;
        private:
            std::vector<std::vector<OBJECT>> map;
            std::vector<std::vector<OBJECT>> mapBomb;
            irr::core::vector2di endMapPos;

    };
}

#endif /* !PATHFINDERCOMPONENT_HPP_ */