/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** InputComponent
*/

#ifndef INPUTCOMPONENT_HPP_
#define INPUTCOMPONENT_HPP_

#include <map>

namespace Indie::Components
{
    enum KEY_TYPE {
        LEFT,
        RIGHT,
        UP,
        DOWN,
        DROP,
        NONE
    };
    class InputComponent
    {
        public:

            InputComponent(std::map<irr::EKEY_CODE, KEY_TYPE> keys);
            ~InputComponent() = default;

            bool isKeyPressed(KEY_TYPE key) const;

            const std::map<irr::EKEY_CODE, KEY_TYPE> &getKeys() const;
            const std::map<irr::EKEY_CODE, bool> &getKeysState() const;

            void setKeys(std::map<irr::EKEY_CODE, KEY_TYPE>);
            void setKeysState(std::map<irr::EKEY_CODE, bool>);

            KEY_TYPE getKeyType(irr::EKEY_CODE);

        protected:
        private:
            std::map<irr::EKEY_CODE, KEY_TYPE> keys;
            std::map<irr::EKEY_CODE, bool> keysState;
    };
}

#endif /* !INPUTCOMPONENT_HPP_ */
