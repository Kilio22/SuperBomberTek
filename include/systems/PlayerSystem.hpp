/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** PlayerSystem
*/

#ifndef PLAYERSYSTEM_HPP_
#define PLAYERSYSTEM_HPP_

#include "ISystem.hpp"

namespace Indie::Systems
{
    class PlayerSystem : public ISystem
    {
    public:
        PlayerSystem() = default;
        ~PlayerSystem() = default;

        void onUpdate(irr::f32 deltaTime, EntityManager &entityManager) const final;
    };
}

#endif /* !PLAYERSYSTEM_HPP_ */
