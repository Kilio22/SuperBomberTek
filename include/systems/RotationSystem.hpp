/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** RotationSystem
*/

#ifndef ROTATIONSYSTEM_HPP_
#define ROTATIONSYSTEM_HPP_

#include "ISystem.hpp"

namespace Indie::Systems
{
    class RotationSystem : public ISystem
    {
        public:
            RotationSystem() = default;
            ~RotationSystem() = default;

            void onUpdate(int ticks, EntityManager &) const final;

        protected:
        private:
    };
}

#endif /* !ROTATIONSYSTEM_HPP_ */
