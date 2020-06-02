/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** PathFinderSystem
*/

#ifndef PATHFINDERSYSTEM_HPP_
#define PATHFINDERSYSTEM_HPP_

#include <irrlicht.h>
#include <math.h>
#include "ISystem.hpp"
#include "EntityManager.hpp"
#include "AIComponent.hpp"
#include "BombComponent.hpp"
#include "PathFinderComponent.hpp"
#include "PositionComponent.hpp"
#include "PowerUpComponent.hpp"
#include "PlayerComponent.hpp"

namespace Indie::Systems
{
    class PathFinderSystem : public ISystem
    {
        public:
            PathFinderSystem() = default;
            ~PathFinderSystem() = default;

            void onUpdate(irr::f32 deltaTime, EntityManager &entityManager) const final;


            int getNbPlayerInZone(std::vector<std::vector<Indie::Components::OBJECT>> map,  EntityManager &entityManager, irr::core::vector2di aiPosition) const;


            void findPosition(std::vector<std::vector<Indie::Components::OBJECT>> &map, Indie::Components::PathFinderComponent *pathFinder, irr::core::vector2di aiPosition) const;
            void findFirstPosition(std::vector<std::vector<Indie::Components::OBJECT>> &map, std::vector<std::vector<Indie::Components::OBJECT>> &mapBomb, Indie::Components::PathFinderComponent *pathFinder, irr::core::vector2di aiPosition) const;

            int getCenter(int value) const;
            bool hasArrived(std::vector<std::vector<Indie::Components::OBJECT>> &map, Indie::Components::PathFinderComponent *pathFinder) const;
            int getDistance2D(irr::core::vector2di v1, irr::core::vector2di v2) const;
            bool goOnBomb(std::vector<std::vector<Indie::Components::OBJECT>> mapBomb, irr::core::vector2di aiPosition, Indie::Components::DIRECTION direction) const;
            //set PathFinding
            void setPathFinding(std::vector<std::vector<Indie::Components::OBJECT>> &map, irr::core::vector2di aiPosition, int value,  std::vector<std::vector<Indie::Components::OBJECT>> mapBomb) const;

            //Get
            void setShortlessPath(std::vector<std::vector<Indie::Components::OBJECT>> &map, irr::core::vector2di acPos, irr::core::vector2di nextPos) const;

            //set Map
            void setMapBomb(std::vector<std::vector<Indie::Components::OBJECT>> &map, EntityManager &entityManager) const;
            void setMapPowerUp(std::vector<std::vector<Indie::Components::OBJECT>> &map, EntityManager &entityManager) const;
            void cleanMap(std::vector<std::vector<Indie::Components::OBJECT>> &map) const;
    };
}

#endif /* !PATHFINDERSYSTEM_HPP_ */
