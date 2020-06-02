/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** ShakeComponent | Author: Kylian BALAN - kylian.balan@epitech.eu
*/

#ifndef SHAKECOMPONENT_HPP_
#define SHAKECOMPONENT_HPP_

#include <irrlicht.h>

namespace Indie::Components
{
    class ShakeComponent
    {
        public:
        ShakeComponent();
        ~ShakeComponent() = default;

        bool getIsShaking(void) const;
        irr::u32 getStartingTime(void) const;
        const irr::core::vector3df &getInitialPosition(void) const;
        const irr::core::vector3df &getInitialTarget(void) const;
        void setIsShaking(bool value);
        void setStartingTime(irr::u32 value);

        private:
        irr::core::vector3df initialPositon;
        irr::core::vector3df initialTarget;
        irr::u32 startingTime;
        bool isShaking;
    };
} // namespace Indie::Components

#endif /* !SHAKECOMPONENT_HPP_ */
