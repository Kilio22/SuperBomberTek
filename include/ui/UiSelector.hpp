/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** UiSelector
*/

#ifndef UISELECTOR_HPP_
#define UISELECTOR_HPP_

#include <utility>
#include <irrlicht.h>

namespace Indie
{
    class UiSelector
    {
        public:
            UiSelector(int sizeX, int sizeY, irr::EKEY_CODE up, irr::EKEY_CODE down, irr::EKEY_CODE left, irr::EKEY_CODE right, bool x = true, bool y = true);
            ~UiSelector() = default;

            void setBLockSound(bool, bool);
            std::pair<int, int> getPos() const;
            void setPos(int posX, int posY);
            void setSize(int sizeX, int sizeY);
            void update();

        private:
            int posX;
            int posY;
            int sizeX;
            int sizeY;
            irr::EKEY_CODE up;
            irr::EKEY_CODE down;
            irr::EKEY_CODE left;
            irr::EKEY_CODE right;
            bool soundX;
            bool soundY;
    };
}

#endif /* !UISELECTOR_HPP_ */
