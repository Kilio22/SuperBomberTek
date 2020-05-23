/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** ISystem
*/

#ifndef ISYSTEM_HPP_
#define ISYSTEM_HPP_

#include "EntityManager.hpp"
#include "ContextManager.hpp"

namespace Indie::Systems
{
    class ISystem
    {
        public:
            virtual ~ISystem() = default;

            virtual void onUpdate(irr::f32 deltaTime, EntityManager &entityManager) const = 0;
    };
}

#endif /* !ISYSTEM_HPP_ */
