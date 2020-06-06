/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** PathFinderComponent
*/

#ifndef PATHFINDERCOMPONENT_HPP_
#define PATHFINDERCOMPONENT_HPP_

#include "MapComponent.hpp"
#include "ServiceLocator.hpp"
#include <irrlicht.h>
#include <vector>

namespace Indie::Components
{
    /**
     * @brief Path finder component
     */
    class PathFinderComponent
    {
    public:
        PathFinderComponent() = default;
        ~PathFinderComponent() = default;

        /**
         * @brief Sets the path map of AI
         * @param map The path map
         */
        void setMap(std::vector<std::vector<OBJECT>> map);

        /**
         * @brief Sets the map with current explosions and future explosions with the range for each bomb
         * @param map The bombed map
         */
        void setMapBomb(std::vector<std::vector<OBJECT>> map);

        /**
         * @brief Sets the final position for the movement of AI
         * @param endPos The final position vector
         */
        void setEndMapPos(irr::core::vector2di endPos);

        /**
         * @brief Gets the path map
         * @return The path map
         */
        std::vector<std::vector<OBJECT>> getMap() const;

        /**
         * @brief Gets the bombed map
         * @return The bombed map
         */
        std::vector<std::vector<OBJECT>> getMapBomb() const;

        /**
         * @brief Gets the final position of AI
         * @return The final position vector
         */
        irr::core::vector2di getEndMapPos() const;

    private:
        std::vector<std::vector<OBJECT>> map;
        std::vector<std::vector<OBJECT>> mapBomb;
        irr::core::vector2di endMapPos;
    };
}

#endif /* !PATHFINDERCOMPONENT_HPP_ */