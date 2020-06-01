/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** MoveSystem
*/

#ifndef MOVESYSTEM_HPP_
#define MOVESYSTEM_HPP_

#include "ISystem.hpp"
#include "EntityManager.hpp"

namespace Indie::Systems
{
    class MoveSystem : public ISystem
    {
        public:
            MoveSystem() = default;
            ~MoveSystem() = default;
            int getCenter(int value) const;
            void onUpdate(irr::f32 deltaTime, EntityManager &entityManager) const final;
    };
}

#endif /* !MOVESYSTEM_HPP_ */
