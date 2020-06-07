/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** AISystem
*/

#ifndef AISYSTEM_HPP_
#define AISYSTEM_HPP_

#include "ISystem.hpp"
#include "AIComponent.hpp"
#include "PathFinderComponent.hpp"
#include "MoveComponent.hpp"
#include "PositionComponent.hpp"
#include <irrlicht.h>
#include <vector>

namespace Indie::Systems
{
    class AISystem : public ISystem
    {
        public:
            AISystem() = default;
            ~AISystem() = default;

            void onUpdate(irr::f32 deltaTime, EntityManager &entityManager) const final;
        private:
            int getCenter(int value) const;
            bool hasDropBomb(EntityManager &entityManager, int idAi) const;
            bool isMoving(Indie::Components::DIRECTION direction, Indie::Components::AIComponent *ai) const;
            bool isOnBomb(std::vector<std::vector<Indie::Components::OBJECT>> map, Indie::Components::PositionComponent *position) const;
            bool hasArrived(std::vector<std::vector<Indie::Components::OBJECT>> &map, Indie::Components::PathFinderComponent *pathFinder) const;

    };
}

#endif /* !AISYSTEM_HPP_ */
