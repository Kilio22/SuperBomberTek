/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** GameSystem
*/

#ifndef GAMESYSTEM_HPP_
#define GAMESYSTEM_HPP_

#include "ISystem.hpp"

namespace Indie::Systems
{
    class GameSystem : public ISystem
    {
    public:
        GameSystem() = default;
        ~GameSystem() = default;

        void onUpdate(irr::f32 deltaTime, EntityManager &entityManager) const final;

    private:
        std::pair<unsigned int, unsigned int> countPlayers(EntityManager &entityManager) const;
    };
}

#endif /* !GAMESYSTEM_HPP_ */
