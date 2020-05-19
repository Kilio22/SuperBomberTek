/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** BombUpComponent
*/

#ifndef BOMBUPCOMPONENT_HPP_
#define BOMBUPCOMPONENT_HPP_

#include "IComponent.hpp"

namespace Indie::Components
{
    class BombUpComponent : public IComponent {
        public:
            BombUpComponent();
            ~BombUpComponent() = default;

            int getNumberBomb() const;
            void setNumberBomb(int numberBomb);
        private:
            int numberBomb;
    };
}

#endif /* !BOMBUPCOMPONENT_HPP_ */
