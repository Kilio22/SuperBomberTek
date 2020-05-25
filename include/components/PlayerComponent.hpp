/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** PlayerComponent
*/

#ifndef PLAYERCOMPONENT_HPP_
#define PLAYERCOMPONENT_HPP_

#include <irrlicht.h>

namespace Indie::Components
{
    class PlayerComponent
    {
        public:
            PlayerComponent();
            ~PlayerComponent() = default;

            unsigned int getBombsRange(void) const;
            unsigned int getMaxBombNb(void) const;
            unsigned int getCurrentBombNb(void) const;

            void setBombsRange(unsigned int value);
            void setMaxBombNb(unsigned int value);
            void setCurrentBombNb(unsigned int value);

        protected:
        private:
            unsigned int bombsRange;
            unsigned int maxBombNb;
            unsigned int currentBombNb;
    };
} // namespace Indie::Components


#endif /* !PLAYERCOMPONENT_HPP_ */
