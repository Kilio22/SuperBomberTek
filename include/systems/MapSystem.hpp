/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** MapSystem
*/

#ifndef MAPSYSTEM_HPP_
#define MAPSYSTEM_HPP_

#include "ISystem.hpp"

namespace Indie::Systems
{
    class MapSystem : public ISystem
    {
        public:
            MapSystem() = default;
            ~MapSystem() = default;

            void onUpdate(irr::f32 deltaTime, EntityManager &entityManager) const final;
            void render(EntityManager &entityManager);
        private:
            void createWallMap(std::vector<std::vector<int>> &map, irr::core::vector2di dimension);
            void createDefaultMap(std::vector<std::vector<int>> &map, irr::core::vector2di dimension);
            void createRandomMap(std::vector<std::vector<int>> &map, irr::core::vector2di dimension);
            void createEmptyMap(std::vector<std::vector<int>> &map, irr::core::vector2di dimension);
            void setSpawn(std::vector<std::vector<int>> &map, irr::core::vector2di dimension);
    };
}
#endif /* !MAPSYSTEM_HPP_ */
