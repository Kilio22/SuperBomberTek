/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** PathFinderSystem
*/

#ifndef PATHFINDERSYSTEM_HPP_
#define PATHFINDERSYSTEM_HPP_

#include "ISystem.hpp"
#include "EntityManager.hpp"
#include "PathFinderComponent.hpp"
#include <irrlicht.h>

namespace Indie::Systems
{
    class PathFinderSystem : public ISystem
    {
        public:
            PathFinderSystem() = default;
            ~PathFinderSystem() = default;

            void onUpdate(irr::f32 deltaTime, EntityManager &entityManager) const final;

        private:
            int getCenter(int value) const;
            int getDistance2D(irr::core::vector2di v1, irr::core::vector2di v2) const;
            void findFirstPosition(std::vector<std::vector<Indie::Components::OBJECT>> &map, std::vector<std::vector<Indie::Components::OBJECT>> &mapBomb, Indie::Components::PathFinderComponent *pathFinder, irr::core::vector2di aiPosition) const;
            void findPosition(std::vector<std::vector<Indie::Components::OBJECT>> &map, Indie::Components::PathFinderComponent *pathFinder, irr::core::vector2di aiPosition) const;
            void setPathFinding(std::vector<std::vector<Indie::Components::OBJECT>> &map, irr::core::vector2di aiPosition, std::vector<std::vector<Indie::Components::OBJECT>> mapBomb, std::vector<std::vector<Indie::Components::OBJECT>> mapPower) const;
            void setShortlessPath(std::vector<std::vector<Indie::Components::OBJECT>> &map, irr::core::vector2di acPos, irr::core::vector2di nextPos) const;
            void setMapPower(std::vector<std::vector<Indie::Components::OBJECT>> &map, EntityManager &entityManager) const;
            void setMapBomb(std::vector<std::vector<Indie::Components::OBJECT>> &map, EntityManager &entityManager) const;
            void cleanMap(std::vector<std::vector<Indie::Components::OBJECT>> &map) const;


    };
}

#endif /* !PATHFINDERSYSTEM_HPP_ */
