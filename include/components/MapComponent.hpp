/*
** EPITECH PROJECT, 2020
** OOP_Indie::Components_studio_2019
** File description:
** MapComponent
*/

#ifndef MAPCOMPONENT_HPP_
#define MAPCOMPONENT_HPP_

#include <vector>
#include <irrlicht.h>

namespace Indie::Components
{
    enum class MAP_TYPE {
        DEFAULT = 0,
        RANDOM = 1,
        EMPTY = 2,
    };

    enum class THEME {
        STONE,
        DIRT,
    };

    enum class OBJECT {
        WALL_OUT = -1,
        VOID = 0,
        WALL_IN = 1,
        BOX = 2,
        BOMB = 3,
        PLAYER = 4,
        LAVA = 5,
    };

    enum class MAP_STATE {
        DEFAULT,
        TRANSPARENT
    };

    class MapComponent
    {
        public:
            MapComponent(const irr::core::vector2di &dimension = irr::core::vector2di(15, 15), MAP_TYPE type = MAP_TYPE::DEFAULT, THEME theme = THEME::STONE);
            ~MapComponent() = default;

            const MAP_TYPE &getType() const;
            const THEME  &getTheme() const;
            const irr::core::vector2di &getDimension() const;
            const std::vector<std::vector<OBJECT>> &getMap() const;
            const MAP_STATE &getMapState() const;

            void setType(MAP_TYPE type);
            void setTheme(THEME theme);
            void setDimension(const irr::core::vector2di &dimension);
            void setMap(const std::vector<std::vector<OBJECT>> &map);
            void setMapState(MAP_STATE newState);

        private:
            irr::core::vector2di dimension;
            MAP_TYPE type;
            THEME theme;
            std::vector<std::vector<OBJECT>> map;
            MAP_STATE mapState;
    };
}


#endif /* !MAPCOMPONENT_HPP_ */
