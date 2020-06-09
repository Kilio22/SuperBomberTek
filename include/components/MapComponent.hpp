/*
** EPITECH PROJECT, 2020
** OOP_Indie::Components_studio_2019
** File description:
** MapComponent
*/

#ifndef MAPCOMPONENT_HPP_
#define MAPCOMPONENT_HPP_

#include <irrlicht.h>
#include <string>
#include <vector>

namespace Indie::Components
{
    enum class MAP_TYPE
    {
        DEFAULT = 0,
        RANDOM = 1,
        EMPTY = 2,
        SAVED
    };

    enum class THEME
    {
        STONE,
        DIRT,
        SNOW
    };

    enum class OBJECT
    {
        WALL_OUT = -1,
        VOID = 0,
        WALL_IN = 1,
        BOX = 2,
        BOMB = 3,
        PLAYER = 4,
        LAVA = 5
    };

    enum class MAP_STATE
    {
        DEFAULT,
        TRANSPARENT
    };

    /**
     * @brief Map component
     */
    class MapComponent
    {
    public:
        MapComponent(const irr::core::vector2di &dimension = irr::core::vector2di(15, 15), MAP_TYPE type = MAP_TYPE::DEFAULT,
            THEME theme = THEME::STONE, const std::string &mapPath = "");
        ~MapComponent() = default;

        /**
         * @brief Gets the map type
         * @return const MAP_TYPE& The map type
         */
        const MAP_TYPE &getType() const;

        /**
         * @brief Gets the map theme
         * @return const THEME& The map them
         */
        const THEME &getTheme() const;

        /**
         * @brief Gets the map's dimensions
         * @return const irr::core::vector2di& The map's dimensions
         */
        const irr::core::vector2di &getDimension() const;

        /**
         * @brief Gets the map
         * @return const std::vector<std::vector<OBJECT>>& The map
         */
        const std::vector<std::vector<OBJECT>> &getMap() const;

        /**
         * @brief Gets the map state
         * @return const MAP_STATE& The map state
         */
        const MAP_STATE &getMapState() const;

        /**
         * @brief Gets the map's path
         *
         * @return const std::string& The map's path
         */
        const std::string &getMapPath(void) const;

        /**
         * @brief Sets the map
         * @param map The map
         */
        void setMap(const std::vector<std::vector<OBJECT>> &map);

        /**
         * @brief Sets the map's state
         * @param newState The state
         */
        void setMapState(MAP_STATE newState);

    private:
        irr::core::vector2di dimension;
        MAP_TYPE type;
        THEME theme;
        std::vector<std::vector<OBJECT>> map;
        MAP_STATE mapState;
        std::string mapPath;
    };
}

#endif /* !MAPCOMPONENT_HPP_ */
