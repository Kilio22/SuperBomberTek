/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** WallPassComponent
*/

#ifndef WALLPASSCOMPONENT_HPP_
#define WALLPASSCOMPONENT_HPP_

#include "AComponent.hpp"

namespace Indie::Components
{
    class WallPassComponent : public AComponent {
        public:
            WallPassComponent();
            ~WallPassComponent() = default;

            bool getWallPass() const;
            void setWallPass(bool status);
        private:
            bool canPass;
    };
}

#endif /* !WALLPASSCOMPONENT_HPP_ */
