/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** AISystem
*/

#ifndef AISYSTEM_HPP_
#define AISYSTEM_HPP_

#include <array>
#include <iostream>
#include <vector>
#include "ISystem.hpp"
#include "AIComponent.hpp"
#include "MapComponent.hpp"
#include "PathFinderComponent.hpp"

namespace Indie::Systems
{
    class AISystem : public ISystem
    {
        public:
            AISystem() = default;
            ~AISystem() = default;

            void onUpdate(irr::f32 deltaTime, EntityManager &entityManager) const final;

            bool hasMoved(irr::core::vector3df position, irr::core::vector3df nextPosition, Indie::Components::AIComponent *aiComponent) const;
            bool isMoving(Indie::Components::DIRECTION direction, Indie::Components::AIComponent *aiComponent) const;
            bool hasArrived(std::vector<std::vector<Indie::Components::OBJECT>> &map, Indie::Components::PathFinderComponent *pathFinderComponent) const;
            int getCenter(int value) const;

    };
}

#endif /* !AISYSTEM_HPP_ */
