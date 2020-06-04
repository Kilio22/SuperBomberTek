/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** RotationComponent
*/

#ifndef ROTATIONCOMPONENT_HPP_
#define ROTATIONCOMPONENT_HPP_

#include <irrlicht.h>

namespace Indie::Components
{
    /**
     * @brief Rotation component
     */
    class RotationComponent
    {
    public:
        RotationComponent(float angleY = 180, float angleX = 0);
        ~RotationComponent() = default;

        /**
         * @brief Gets the current 3D rotation vector
         * @return const irr::core::vector3df& The 3D rotation vector
         */
        const irr::core::vector3df &getAngle(void) const;

        /**
         * @brief Sets the Y angle of the 3D rotation vector
         * @param newAngle The new Y angle
         */
        void setYAngle(float newAngle);

    private:
        irr::core::vector3df angle;
    };
}

#endif /* !ROTATIONCOMPONENT_HPP_ */
