/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** MapGenerator
*/

#ifndef MAPGENERATOR_HPP_
#define MAPGENERATOR_HPP_


#include "EntityBuilder.hpp"
#include <irrlicht.h>

namespace Indie
{
    class MapGenerator
    {
        public:
            MapGenerator(Indie::EntityBuilder &entityBuilder, irr::core::vector2di vector, Indie::Components::MAP_TYPE type, Indie::Components::THEME theme);
            ~MapGenerator() = default;

            void generate(Indie::EntityManager &entityManager, Indie::EntityBuilder &entityBuilder);
        private:
            void createWallMap(std::vector<std::vector<int>> &map, irr::core::vector2di dimension);
            void createDefaultMap(std::vector<std::vector<int>> &map, irr::core::vector2di dimension);
            void createRandomMap(std::vector<std::vector<int>> &map, irr::core::vector2di dimension);
            void createEmptyMap(std::vector<std::vector<int>> &map, irr::core::vector2di dimension);
            void setSpawn(std::vector<std::vector<int>> &map, irr::core::vector2di dimension);
    };
}



#endif /* !MAPGENERATOR_HPP_ */
