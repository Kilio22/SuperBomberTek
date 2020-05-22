/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** CollisionSystem
*/

#ifndef COLLISIONSYSTEM_HPP_
#define COLLISIONSYSTEM_HPP_

#include "ISystem.hpp"

namespace Indie::Systems
{
    class CollisionSystem : public ISystem
    {
        public:
            CollisionSystem() = default;
            ~CollisionSystem() = default;

            void onUpdate(int ticks, EntityManager &entityManager, const ContextManager &contextManager) const final;

        protected:
        private:
    };
} // namespace Indie::Systems


#endif /* !COLLISIONSYSTEM_HPP_ */
