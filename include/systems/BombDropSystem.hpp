/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** BombDropSystem
*/

#ifndef BOMBDROPSYSTEM_HPP_
#define BOMBDROPSYSTEM_HPP_

#include "ISystem.hpp"
#include "Components.h"
#include "EntityManager.hpp"
#include "ContextManager.hpp"

namespace Indie::Systems
{
    class BombDropSystem : public ISystem
    {
        public:
            BombDropSystem() = default;
            ~BombDropSystem() = default;

            void onUpdate(irr::f32 deltaTime, EntityManager &entityManager) const final;

        private:
            bool hasBombAtPosition(EntityManager &entityManager, irr::core::vector3df position) const;
            int getCenter(int value) const;
            std::vector<std::vector<Indie::Components::OBJECT>> updateMap(std::vector<std::vector<Indie::Components::OBJECT>> currentMap, irr::f32 midX, irr::f32 midZ) const;
    };
}

#endif /* !BOMBDropSYSTEM_HPP_ */
