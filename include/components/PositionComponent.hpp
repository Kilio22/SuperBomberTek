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
    /**
     * @brief Position component
     */
    class PositionComponent
    {
    public:
        PositionComponent(float posX, float posY, float posZ);
        ~PositionComponent() = default;

        /**
         * @brief Gets the stored position
         * @return const irr::core::vector3df& The position
         */
        const irr::core::vector3df &getPosition(void) const;

        /**
         * @brief Sets the stored position
         * @param position The new position
         */
        void setPosition(irr::core::vector3df position);

    private:
        irr::core::vector3df position;
    };
}

#endif /* !POSITIONCOMPONENT_HPP_ */
