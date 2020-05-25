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
    };

    class MapComponent
    {
        public:
            MapComponent(const irr::core::vector2di &dimension, const Indie::Components::MAP_TYPE &type, const Indie::Components::THEME &theme);
            ~MapComponent() = default;

            Indie::Components::MAP_TYPE getType() const;
            Indie::Components::THEME  getTheme() const;
            irr::core::vector2di getDimension() const;
            std::vector<std::vector<int>> getMap() const;

            void setType(Indie::Components::MAP_TYPE type);
            void setTheme(Indie::Components::THEME theme);
            void setDimension(irr::core::vector2di dimension);
            void setMap(std::vector<std::vector<int>> map);

        private:
            Indie::Components::MAP_TYPE type = Indie::Components::MAP_TYPE::DEFAULT;
            Indie::Components::THEME theme = Indie::Components::THEME::STONE;
            irr::core::vector2di dimension = irr::core::vector2di(15, 15);
            std::vector<std::vector<int>> map;
    };
}


#endif /* !MAPCOMPONENT_HPP_ */
