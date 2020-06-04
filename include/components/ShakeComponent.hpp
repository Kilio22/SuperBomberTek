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
    /**
     * @brief Shake component
     */
    class ShakeComponent
    {
    public:
        ShakeComponent();
        ~ShakeComponent() = default;

        /**
         * @brief Gets the isShaking boolean value
         *
         * @return true The screen is shaking
         * @return false The screen is not shaking
         */
        bool getIsShaking(void) const;

        /**
         * @brief Gets the delta time
         * @return irr::f32 The delta time
         */
        irr::f32 getDeltaTime(void) const;

        /**
         * @brief Gets the initial camera's position
         * @return const irr::core::vector3df& The position
         */
        const irr::core::vector3df &getInitialPosition(void) const;

        /**
         * @brief Gets the initial camera's target
         * @return const irr::core::vector3df& The target
         */
        const irr::core::vector3df &getInitialTarget(void) const;

        /**
         * @brief Sets the isShaking boolean
         * @param value The new value
         */
        void setIsShaking(bool value);

        /**
         * @brief Sets the delta time
         * @param value The new delta time
         */
        void setDeltaTime(irr::f32 value);

    private:
        irr::core::vector3df initialPositon;
        irr::core::vector3df initialTarget;
        irr::f32 deltaTime;
        bool isShaking;
    };
} // namespace Indie::Components

#endif /* !SHAKECOMPONENT_HPP_ */
