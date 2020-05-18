/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** AComponent
*/

#ifndef ACOMPONENT_HPP_
#define ACOMPONENT_HPP_

#include "IComponent.hpp"

namespace Indie::Components
{
    class AComponent : public IComponent
    {
        public:
            AComponent(int id);
            ~AComponent() = default;

        protected:
            int id;
    };
}

#endif /* !ACOMPONENT_HPP_ */
