/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** VelocityComponent
*/

#ifndef VELOCITYCOMPONENT_HPP_
#define VELOCITYCOMPONENT_HPP_

namespace Indie::Components
{
    /**
     * @brief Velocity component
     */
    class VelocityComponent
    {
    public:
        VelocityComponent();
        ~VelocityComponent() = default;

        /**
         * @brief Gets the velocity
         * @return float The velocity
         */
        float getVelocity(void) const;

        /**
         * @brief Sets the velocity
         * @param newVel The new velocity
         */
        void setVelocity(float newVel);

    private:
        float velocity;
    };
}

#endif /* !VELOCITYCOMPONENT_HPP_ */
