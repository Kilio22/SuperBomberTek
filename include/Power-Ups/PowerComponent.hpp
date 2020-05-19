/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** PowerComponent
*/

#ifndef POWERCOMPONENT_HPP_
#define POWERCOMPONENT_HPP_

#include "IComponent.hpp"

namespace Indie::Components
{
    class PowerComponent : public IComponent {
        public:
            PowerComponent();
            ~PowerComponent() = default;

            int getPower() const;
            void setPower(int power);
        private:
            int power;
    };
}

#endif /* !POWERCOMPONENT_HPP_ */
