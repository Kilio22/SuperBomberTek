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
            enum type{
                DEFAULT = 0,
                RANDOM = 1,
                EMPTY = 2,
            };

            enum theme{
                STONE,
                DIRT,
            };
            MapGenerator(enum type type, enum theme theme, int x, int y);
            ~MapGenerator() = default;
            void setType(enum type type);
            void setTheme(enum theme theme);
            void setDimension(int x, int y);
            void generate(EntityManager &entityManager, ContextManager &contextManager);
        protected:
        private:
            enum object{
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
            enum theme _theme;
            enum type _type;
    };
}

#endif /* !MAPGENERATOR_HPP_ */
