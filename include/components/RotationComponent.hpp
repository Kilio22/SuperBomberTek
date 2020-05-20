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
            RotationComponent();
            ~RotationComponent() = default;

            irr::core::vector3df getAngle();
            void setAngle(float newAngle);

        protected:
        private:
            irr::core::vector3df angle;
    };
}

#endif /* !ROTATIONCOMPONENT_HPP_ */
