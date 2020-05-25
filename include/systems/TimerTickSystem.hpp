/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** TimerTickSystem
*/

#ifndef TIMERTICKSYSTEM_HPP_
#define TIMERTICKSYSTEM_HPP_

#include "ISystem.hpp"

namespace Indie::Systems {

class TimerTickSystem : public ISystem {
    public:
        TimerTickSystem() = default;
        ~TimerTickSystem() = default;

        void onUpdate(irr::f32 deltaTime, EntityManager &entityManager) const final;
};

}

#endif /* !TIMERTICKSYSTEM_HPP_ */
