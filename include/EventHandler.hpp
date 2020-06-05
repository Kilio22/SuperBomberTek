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
    /**
     * @brief EventHandler singleton class
     */
    class EventHandler : public irr::IEventReceiver
    {
    public:
        ~EventHandler() = default;

        /**
         * @brief Gets the instance of the class
         * @return EventHandler& The instance
         */
        static EventHandler &getInstance();

        /**
         * @brief Called automatically by irrlicht when an event happens. It stores key informations
         * @param event The generated irrlicht event
         */
        bool OnEvent(const irr::SEvent &event) final;

        /**
         * @brief Checks if given key is pressed or not
         * @param key The key to check
         * @return true The key is pressed
         * @return false The key is not pressed
         */
        bool isKeyPressed(irr::EKEY_CODE key) const;

        /**
         * @brief Checks if the given key is pressed at once
         * @param key The key to check
         * @return true The key is pressed
         * @return false The key is not pressed
         */
        bool isKeyPressedAtOnce(irr::EKEY_CODE key) const;

        /**
         * @brief Checks if given key has been released
         * @param key The key to check
         * @return true The key has been released
         * @return false The key hasn't been released
         */
        bool isKeyReleased(irr::EKEY_CODE key) const;

        /**
         * @brief Checks if any key is pressed
         * @return true A key has been pressed
         * @return false No key has been pressed
         */
        bool isAnyKeyPressed() const;

        /**
         * @brief Checks if any key is pressed at once
         * @return true A key has been pressed
         * @return false No key has been pressed
         */
        bool isAnyKeyPressedAtOnce() const;

        /**
         * @brief Resets all the key sets
         */
        void resetKeys(void);

        /**
         * @brief Resets the keys status
         */
        void resetKeysStatus(void);

        /**
         * @brief Resets the keys status pressed once
         */
        void resetKeysStatusOnce(void);

        /**
         * @brief Resets the keys status released
         */
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
