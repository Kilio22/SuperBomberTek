/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** BombExplosionSystem
*/

#ifndef BOMBEXPLOSIONSYSTEM_HPP_
#define BOMBEXPLOSIONSYSTEM_HPP_

#include "ISystem.hpp"

namespace Indie::Systems
{

class BombExplosionSystem : public ISystem
{
    public:
        BombExplosionSystem() = default;
        ~BombExplosionSystem() = default;

        void onUpdate(irr::f32 deltaTime, EntityManager &entityManager) const final;
};

}

#endif /* !BOMBEXPLOSIONSYSTEM_HPP_ */
