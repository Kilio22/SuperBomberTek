/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** ISystem
*/

#ifndef ISYSTEM_HPP_
#define ISYSTEM_HPP_

#include "EntityManager.hpp"

namespace Indie::System
{
    class ISystem
    {
        public:
            virtual ~ISystem() = default;

            virtual void onUpdate(int ticks, EntityManager &) = 0;

        protected:
        private:
    };
}

#endif /* !ISYSTEM_HPP_ */
