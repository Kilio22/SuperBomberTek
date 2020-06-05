/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** ISystem
*/

#ifndef ISYSTEM_HPP_
#define ISYSTEM_HPP_

#include "ContextManager.hpp"
#include "EntityManager.hpp"

namespace Indie::Systems
{
    /**
     * @brief ISystem interface. All systems must inherit this interface
     */
    class ISystem
    {
    public:
        virtual ~ISystem() = default;

        /**
         * @brief Updates things according to system type.
         *
         * @param deltaTime The time elapsed since the last time this method has been called. It's very useful for framerate independence.
         * @param entityManager The entity manager
         */
        virtual void onUpdate(irr::f32 deltaTime, EntityManager &entityManager) const = 0;
    };
}

#endif /* !ISYSTEM_HPP_ */
