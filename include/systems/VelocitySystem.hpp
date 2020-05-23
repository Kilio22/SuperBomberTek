/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** VelocitySystem
*/

#ifndef VELOCITYSYSTEM_HPP_
#define VELOCITYSYSTEM_HPP_

#include "ISystem.hpp"

namespace Indie::Systems
{
    class VelocitySystem : public ISystem
    {
        public:
            VelocitySystem() = default;
            ~VelocitySystem() = default;

            void onUpdate(irr::f32 deltaTime, EntityManager &entityManager, const ContextManager &contextManager) const final;

        protected:
        private:
            static const irr::f32 VELOCITY;
    };
}

#endif /* !VELOCITYSYSTEM_HPP_ */