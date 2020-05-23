/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** MapGenerator
*/

#ifndef MAPGENERATOR_HPP_
#define MAPGENERATOR_HPP_

#include "ContextManager.hpp"
#include "EntityBuilder.h"
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <utility>
#include <vector>

namespace Indie {
    class MapGenerator {
        public:
            enum class MAP_TYPE {
                DEFAULT = 0,
                RANDOM = 1,
                EMPTY = 2,
            };

            enum class THEME {
                STONE,
                DIRT,
            };

            MapGenerator();
            ~MapGenerator() = default;

            void setType(MAP_TYPE type);
            void setTheme(THEME theme);
            void setDimension(int x, int y);
            void generate();
            std::vector<std::vector<int>> getMap() const;

        private:
            enum class OBJECT {
                EXT_WALL = -1,
                VOID = 0,
                BOX = 1,
                IN_WALL = 2,
            };

            void clearMap();
            void createRandomMap(int percentageBox, int percentageWall);
            void createDefaultMap();
            void setSpawn();

            std::vector<std::vector<int>> _map;
            int _x = 15;
            int _y = 15;
            THEME _theme = THEME::STONE;
            MAP_TYPE _type = MAP_TYPE::DEFAULT;
    };
}

#endif /* !MAPGENERATOR_HPP_ */
