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
    class VelocityComponent
    {
        public:
            VelocityComponent();
            ~VelocityComponent() = default;

            float getVelocity(void) const;
            void setVelocity(float newVel);

        protected:
        private:
            float velocity;
    };
}

#endif /* !VELOCITYCOMPONENT_HPP_ */
