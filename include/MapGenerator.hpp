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
        MapGenerator(Indie::EntityBuilder &entityBuilder, irr::core::vector2di vector, Indie::Components::MAP_TYPE type,
            Indie::Components::THEME theme, const std::string &mapPath);
        ~MapGenerator() = default;

        /**
         * @brief Generates a map which take in account parameters given in ctor
         * @param entityManager The entity manager
         * @param entityBuilder The entity builder
         */
        void generate(Indie::EntityManager &entityManager, Indie::EntityBuilder &entityBuilder);

        private:
        void createWallMap(std::vector<std::vector<Components::OBJECT>> &map, irr::core::vector2di dimension);
        void createDefaultMap(std::vector<std::vector<Components::OBJECT>> &map, irr::core::vector2di dimension);
        void createRandomMap(std::vector<std::vector<Components::OBJECT>> &map, irr::core::vector2di dimension);
        void createEmptyMap(std::vector<std::vector<Components::OBJECT>> &map, irr::core::vector2di dimension);
        void createSavedMap(std::vector<std::vector<Components::OBJECT>> &map, const std::string &mapPath, irr::core::vector2di dimension);
        void setSpawn(std::vector<std::vector<Components::OBJECT>> &map, irr::core::vector2di dimension);
    };
}

#endif /* !MAPGENERATOR_HPP_ */
