/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** KickBombComponent
*/

#ifndef KICKBOMBCOMPONENT_HPP_
#define KICKBOMBCOMPONENT_HPP_

#include "AComponent.hpp"

namespace Indie::Components
{
    class KickBombComponent : public AComponent {
        public:
            KickBombComponent();
            ~KickBombComponent() = default;
            
            bool getKickStatus() const;
            void setKickStatus(bool status);
        private:
            bool canKick;
    };
}

#endif /* !KICKBOMBCOMPONENT_HPP_ */
