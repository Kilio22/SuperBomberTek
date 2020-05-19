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
#include "InputComponent.hpp"

namespace Indie::Systems
{
    class InputSystem : public ISystem
    {
        public:
            InputSystem();
            ~InputSystem() = default;

            void onUpdate(int ticks, EntityManager &);

        protected:
        private:
            EventHandler &eventHandler;

            std::map<irr::EKEY_CODE, bool> updateKeys(std::map<irr::EKEY_CODE, bool>, std::shared_ptr<Indie::Components::InputComponent> &);
    };
}

#endif /* !INPUTSYSTEM_HPP_ */
