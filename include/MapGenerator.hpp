/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** MapGenerator
*/

#ifndef MAPGENERATOR_HPP_
#define MAPGENERATOR_HPP_

#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <ctime>
#include <vector>
#include <utility>
#include "EntityManager.hpp"
#include "ContextManager.hpp"
#include "EntityBuilder.h"


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

            MapGenerator(MAP_TYPE type, THEME theme, int x, int y);
            ~MapGenerator() = default;
            void setType(MAP_TYPE type);
            void setTheme(THEME theme);
            void setDimension(int x, int y);
            void generate(EntityManager &entityManager, ContextManager &contextManager);
        protected:
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
            int _x;
            int _y;
            THEME _theme;
            MAP_TYPE _type;
    };
}

#endif /* !MAPGENERATOR_HPP_ */
