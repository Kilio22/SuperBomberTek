/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** ShakeSystem | Author: Kylian BALAN - kylian.balan@epitech.eu
*/

#ifndef SHAKESYSTEM_HPP_
#define SHAKESYSTEM_HPP_

#include "ISystem.hpp"

namespace Indie::Systems
{
    class ShakeSystem : public ISystem
    {
        public:
        ShakeSystem() = default;
        ~ShakeSystem() = default;

        void onUpdate(irr::f32 deltaTime, EntityManager &entityManager) const final;
    };
} // namespace Indie::Systems

#endif /* !SHAKESYSTEM_HPP_ */
