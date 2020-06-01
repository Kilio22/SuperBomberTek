/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** PlayerComponent
*/

#ifndef PLAYERCOMPONENT_HPP_
#define PLAYERCOMPONENT_HPP_

#include <irrlicht.h>
#include <string>

namespace Indie::Components
{
    class PlayerComponent
    {
        public:
            enum class PLAYER_COLOR {
                RED,
                BLUE,
                YELLOW,
                GENERIC,
                GREEN,
                PURPLE
            };

            PlayerComponent(const std::string &playerNb, PLAYER_COLOR playerColor);
            ~PlayerComponent() = default;

            unsigned int getBombsRange(void) const;
            unsigned int getMaxBombNb(void) const;
            unsigned int getCurrentBombNb(void) const;
            unsigned int getVelocityLevel(void) const;
            bool getWallPass(void) const;
            const std::string &getName(void) const;
            const PLAYER_COLOR &getPlayerColor(void) const;

            void setBombsRange(unsigned int value);
            void setMaxBombNb(unsigned int value);
            void setCurrentBombNb(unsigned int value);
            void setVelocityLevel(unsigned int value);
            void setWallPass(bool value);

        private:
            unsigned int bombsRange;
            unsigned int maxBombNb;
            unsigned int currentBombNb;
            unsigned int velocityLevel;
            bool wallPass;
            std::string name;
            PLAYER_COLOR playerColor;
    };
} // namespace Indie::Components

#endif /* !PLAYERCOMPONENT_HPP_ */
