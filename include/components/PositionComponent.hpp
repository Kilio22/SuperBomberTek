/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** PositionComponent
*/

#ifndef POSITIONCOMPONENT_HPP_
#define POSITIONCOMPONENT_HPP_

#include <irrlicht.h>

namespace Indie::Components
{
    class PositionComponent
    {
        public:
            PositionComponent(float posX, float posY, float posZ);
            ~PositionComponent() = default;

            const irr::core::vector3df &getPosition(void) const;
            void setPosition(irr::core::vector3df position);

        private:
            irr::core::vector3df position;
    };
}

#endif /* !POSITIONCOMPONENT_HPP_ */
