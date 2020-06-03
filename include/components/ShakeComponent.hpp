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
        irr::f32 getDeltaTime(void) const;
        const irr::core::vector3df &getInitialPosition(void) const;
        const irr::core::vector3df &getInitialTarget(void) const;
        void setIsShaking(bool value);
        void setDeltaTime(irr::f32 value);

        private:
        irr::core::vector3df initialPositon;
        irr::core::vector3df initialTarget;
        irr::f32 deltaTime;
        bool isShaking;
    };
} // namespace Indie::Components

#endif /* !SHAKECOMPONENT_HPP_ */
