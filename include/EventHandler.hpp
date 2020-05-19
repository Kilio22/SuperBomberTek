/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** EventHandler
*/

#ifndef EVENTHANDLER_HPP_
#define EVENTHANDLER_HPP_

#include <irrlicht.h>
#include <vector>

namespace Indie
{
    class EventHandler : public irr::IEventReceiver
    {
        public:
            ~EventHandler() = default;

            static EventHandler &getInstance();

            bool OnEvent(const irr::SEvent &event) final;

            bool isKeyPressed(irr::EKEY_CODE);
            bool isKeyPressedAtOnce(irr::EKEY_CODE);
            bool isKeyReleased(irr::EKEY_CODE);

            void operator=(EventHandler const &) = delete;
            EventHandler(EventHandler const &) = delete;

        protected:
        private:
            EventHandler();

            std::vector<bool> keysStatus;
            std::vector<bool> keysStatusOnce;
            std::vector<bool> keysStatusReleased;
    };
}

#endif /* !EVENTHANDLER_HPP_ */
