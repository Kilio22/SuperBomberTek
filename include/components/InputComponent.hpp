/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** InputComponent
*/

#ifndef INPUTCOMPONENT_HPP_
#define INPUTCOMPONENT_HPP_

#include <irrlicht.h>
#include <unordered_map>

namespace Indie::Components
{
    enum class KEY_TYPE
    {
        LEFT,
        RIGHT,
        UP,
        DOWN,
        DROP,
        NONE
    };

    /**
     * @brief Hitbox component
     */
    class InputComponent
    {
    public:
        InputComponent(std::unordered_map<irr::EKEY_CODE, KEY_TYPE> keys);
        ~InputComponent() = default;

        /**
         * @brief Checks if given key is pressed or not
         * @param key The KEY_TYPE (see enum)
         * @return true The key is pressed
         * @return false The key is not pressed
         */
        bool isKeyPressed(KEY_TYPE key) const;

        /**
         * @brief Gets watched keys state
         * @return const std::unordered_map<irr::EKEY_CODE, bool>& List with the state of each watched key
         */
        const std::unordered_map<irr::EKEY_CODE, bool> &getKeysState(void) const;

        /**
         * @brief Sets keys to watch
         * @param newKeys Keys to watch
         */
        void setKeys(std::unordered_map<irr::EKEY_CODE, KEY_TYPE> newKeys);

        /**
         * @brief Sets watched keys state
         * @param newKeysState Watched keys state
         */
        void setKeysState(std::unordered_map<irr::EKEY_CODE, bool> newKeysState);

        /**
         * @brief Gets KEY_TYPE which corresponds to its irr::EKEY_CODE
         * @param key The key code
         * @return KEY_TYPE The key type
         */
        KEY_TYPE getKeyType(irr::EKEY_CODE key) const;

    private:
        std::unordered_map<irr::EKEY_CODE, KEY_TYPE> keys;
        std::unordered_map<irr::EKEY_CODE, bool> keysState;
    };
}

#endif /* !INPUTCOMPONENT_HPP_ */
