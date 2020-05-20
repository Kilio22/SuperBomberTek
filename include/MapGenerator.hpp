/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** MapGenerator
*/

#ifndef MAPGENERATOR_HPP_
#define MAPGENERATOR_HPP_

#include "vector"

namespace Indie {
    class MapGenerator {
        public:
            enum type_map{
                DEFAULT = 0,
                RANDOM = 1,
            };

            MapGenerator(enum type_map type);
            ~MapGenerator();
            

            
            std::vector<std::vector<int>> getMap();

        protected:
        private:
            enum object{
                EXT_WALL = -1,
                EMPTY = 0,
                BOX = 1,
                IN_WALL = 2,
            };
            void createRandomMap();
            void createDefaultMap();
            void setSpawn();
            std::vector<std::vector<int>> _map;
    };
}

#endif /* !MAPGENERATOR_HPP_ */
