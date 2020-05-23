/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** InputSystem
*/

#ifndef INPUTSYSTEM_HPP_
#define INPUTSYSTEM_HPP_

#include <map>
#include "ISystem.hpp"
#include "EventHandler.hpp"
#include "Components.h"

namespace Indie::Systems
{
    class InputSystem : public ISystem
    {
        public:
            InputSystem() = default;
            ~InputSystem() = default;

            void onUpdate(irr::f32 deltaTime, EntityManager &entityManager) const final;

        private:
            std::map<irr::EKEY_CODE, bool> updateKeys(std::map<irr::EKEY_CODE, bool>, Indie::Components::InputComponent *inputComp) const;
    };
}

#endif /* !INPUTSYSTEM_HPP_ */
