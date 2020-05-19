/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** VelocityComponent
*/

#ifndef VELOCITYCOMPONENT_HPP_
#define VELOCITYCOMPONENT_HPP_

#include "IComponent.hpp"

namespace Indie::Components
{
    class VelocityComponent : public IComponent
    {
        public:
            VelocityComponent();
            ~VelocityComponent() = default;

            float getVelocity();
            void setVelocity(float newVel);

        protected:
        private:
            float velocity;
    };
}

#endif /* !VELOCITYCOMPONENT_HPP_ */
