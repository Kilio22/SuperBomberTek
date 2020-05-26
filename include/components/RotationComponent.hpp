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
    class RotationComponent
    {
        public:
            RotationComponent(float angleY = 180, float angleX = 0);
            ~RotationComponent() = default;

            const irr::core::vector3df &getAngle(void) const;
            void setYAngle(float newAngle);
            void setXAngle(float newAngle);

        private:
            irr::core::vector3df angle;
    };
}

#endif /* !ROTATIONCOMPONENT_HPP_ */
