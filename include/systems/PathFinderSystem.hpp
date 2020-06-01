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

namespace Indie::Systems
{
    class PathFinderSystem : public ISystem
    {
        public:
            PathFinderSystem() = default;
            ~PathFinderSystem() = default;

            int getCenter(int value) const;
            void getOposateDirection(Indie::Components::AIComponent *ai, Indie::Components::PathFinderComponent *pathFinder, irr::core::vector2di position) const;
            bool hasArrived(std::vector<std::vector<Indie::Components::OBJECT>> &map, Indie::Components::PathFinderComponent *pathFinder) const;
            void setPathFinding(std::vector<std::vector<Indie::Components::OBJECT>> &map, irr::core::vector2di aiPosition, int value,  std::vector<std::vector<Indie::Components::OBJECT>> mapBomb) const;
            void findPosition(std::vector<std::vector<Indie::Components::OBJECT>> &map, Indie::Components::PathFinderComponent *pathFinder, irr::core::vector2di aiPosition) const;
            void findPowerUP(std::vector<std::vector<Indie::Components::OBJECT>> &map, std::vector<std::vector<Indie::Components::OBJECT>> &mapPowerUp, std::vector<std::vector<Indie::Components::OBJECT>> &mapBomb, Indie::Components::PathFinderComponent *pathFinder, irr::core::vector2di aiPosition) const;
            void findFirstPosition(std::vector<std::vector<Indie::Components::OBJECT>> &map, std::vector<std::vector<Indie::Components::OBJECT>> &mapBomb, Indie::Components::PathFinderComponent *pathFinder) const;
            void setPathFindingBombDodge(std::vector<std::vector<Indie::Components::OBJECT>> &map, irr::core::vector2di aiPosition, int value, std::vector<std::vector<Indie::Components::OBJECT>> mapBomb) const;
            void getShortlessPath(std::vector<std::vector<Indie::Components::OBJECT>> &map, irr::core::vector2di acPos, irr::core::vector2di nextPos) const;
            void setMapBomb(std::vector<std::vector<Indie::Components::OBJECT>> &map, EntityManager &entityManager) const;
            void setMapPowerUp(std::vector<std::vector<Indie::Components::OBJECT>> &map, EntityManager &entityManager) const;
            int getDistance2D(irr::core::vector2di v1, irr::core::vector2di v2) const;
            void onUpdate(irr::f32 deltaTime, EntityManager &entityManager) const final;
    };
}

#endif /* !PATHFINDERSYSTEM_HPP_ */
