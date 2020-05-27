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

            bool isKeyPressed(irr::EKEY_CODE key) const;
            bool isKeyPressedAtOnce(irr::EKEY_CODE key) const;
            bool isKeyReleased(irr::EKEY_CODE key) const;
            bool isAnyKeyPressed() const;
            bool isAnyKeyPressedAtOnce() const;

            void resetKeys(void);
            void resetKeysStatus(void);
            void resetKeysStatusOnce(void);
            void resetKeysReleased(void);

            void operator=(EventHandler const &) = delete;
            EventHandler(EventHandler const &) = delete;

        private:
            EventHandler();

            std::vector<bool> keysStatus;
            std::vector<bool> keysStatusOnce;
            std::vector<bool> keysStatusReleased;
    };
}

#endif /* !EVENTHANDLER_HPP_ */
