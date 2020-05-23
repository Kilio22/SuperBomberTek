/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** AISystem
*/

#ifndef AISYSTEM_HPP_
#define AISYSTEM_HPP_

#include <array>
#include <iostream>
#include <vector>
#include "ISystem.hpp"

namespace Indie::Systems
{
    class AISystem : public ISystem
    {
        public:
            AISystem() = default;
            ~AISystem() = default;

            void onUpdate(irr::f32 deltaTime, EntityManager &entityManager) const final;
        protected:
        private:
    };
}

#endif /* !AISYSTEM_HPP_ */
