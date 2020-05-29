/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** LavaSystem
*/

#ifndef LAVASYSTEM_HPP_
#define LAVASYSTEM_HPP_

#include "ISystem.hpp"
#include "Components.h"

namespace Indie::Systems
{
    class LavaSystem : public ISystem
    {
    public:
        LavaSystem() = default;
        ~LavaSystem() = default;

        void onUpdate(irr::f32 deltaTime, EntityManager &entityManager) const final;

    private:
        void removeElementFromMap(std::vector<std::vector<Components::OBJECT>> &map, Entity *entity) const;
    };

}

#endif /* !LAVASYSTEM_HPP_ */
