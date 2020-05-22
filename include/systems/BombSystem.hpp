/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** BombSystem
*/

#ifndef BOMBSYSTEM_HPP_
#define BOMBSYSTEM_HPP_

#include "ISystem.hpp"
#include "EntityManager.hpp"
#include "ContextManager.hpp"

namespace Indie::Systems
{
    class BombSystem : public ISystem
    {
        public:
            BombSystem() = default;
            ~BombSystem() = default;

            void onUpdate(irr::f32 deltaTime, EntityManager &entityManager, const ContextManager &contextManager) const final;

        protected:
        private:
            bool hasBombAtPosition(EntityManager &entityManager, irr::core::vector3df position) const;
            int getCenter(int value) const;
    };
}

#endif /* !BOMBSYSTEM_HPP_ */
