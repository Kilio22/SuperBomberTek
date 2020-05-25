/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** TimerStopSystem
*/

#ifndef TIMERSTOPSYSTEM_HPP_
#define TIMERSTOPSYSTEM_HPP_

#include "ISystem.hpp"

namespace Indie::Systems {

class TimerStopSystem : public ISystem {
    public:
        TimerStopSystem() = default;
        ~TimerStopSystem() = default;

        void onUpdate(irr::f32 deltaTime, EntityManager &entityManager) const final;
};

}

#endif /* !TIMERSTOPSYSTEM_HPP_ */
