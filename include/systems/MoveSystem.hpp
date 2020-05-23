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

            void onUpdate(irr::f32 deltaTime, EntityManager &entityManager) const final;

        protected:
        private:
    };
}

#endif /* !MOVESYSTEM_HPP_ */
