/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** PositionSystem
*/

#ifndef POSITIONSYSTEM_HPP_
#define POSITIONSYSTEM_HPP_

#include "ISystem.hpp"

namespace Indie::Systems
{
    class PositionSystem : public ISystem
    {
        public:
            PositionSystem() = default;
            ~PositionSystem() = default;

            void onUpdate(int ticks, EntityManager &) final;

        protected:
        private:
    };
}

#endif /* !POSITIONSYSTEM_HPP_ */
