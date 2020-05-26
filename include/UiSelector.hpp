/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** UiSelector
*/

#ifndef UISELECTOR_HPP_
#define UISELECTOR_HPP_

#include "ContextManager.hpp"
#include "EventHandler.hpp"
#include <irrlicht.h>

namespace Indie {
    class UiSelector {
        public:
            UiSelector(int sizeX, int sizeY, irr::EKEY_CODE up, irr::EKEY_CODE down, irr::EKEY_CODE left, irr::EKEY_CODE right);
            ~UiSelector();

            std::pair<int, int> getPos() const;
            void setPos(int posX, int posY);
            void update();

        protected:
        private:
            int posX;
            int posY;
            int sizeX;
            int sizeY;
            irr::EKEY_CODE up;
            irr::EKEY_CODE down;
            irr::EKEY_CODE left;
            irr::EKEY_CODE right;
    };
}

#endif /* !UISELECTOR_HPP_ */