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
    };

    class MapComponent
    {
        public:
            MapComponent(const irr::core::vector2di &dimension, const Indie::Components::MAP_TYPE &type, const Indie::Components::THEME &theme);
            ~MapComponent() = default;

            const Indie::Components::MAP_TYPE &getType() const;
            const Indie::Components::THEME  &getTheme() const;
            const irr::core::vector2di &getDimension() const;
            const std::vector<std::vector<Components::OBJECT>> &getMap() const;

            void setType(Indie::Components::MAP_TYPE type);
            void setTheme(Indie::Components::THEME theme);
            void setDimension(irr::core::vector2di dimension);
            void setMap(std::vector<std::vector<Components::OBJECT>> map);

        private:
            Indie::Components::MAP_TYPE type = Indie::Components::MAP_TYPE::DEFAULT;
            Indie::Components::THEME theme = Indie::Components::THEME::STONE;
            irr::core::vector2di dimension = irr::core::vector2di(15, 15);
            std::vector<std::vector<Components::OBJECT>> map;
    };
}


#endif /* !MAPCOMPONENT_HPP_ */
