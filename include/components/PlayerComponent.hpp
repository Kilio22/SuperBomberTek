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
            PlayerComponent(const std::string &playerNb);
            ~PlayerComponent() = default;

            unsigned int getBombsRange(void) const;
            unsigned int getMaxBombNb(void) const;
            unsigned int getCurrentBombNb(void) const;
            unsigned int getVelocityLevel(void) const;
            bool getWallPass(void) const;
            const std::string &getName(void) const;

            void setBombsRange(unsigned int value);
            void setMaxBombNb(unsigned int value);
            void setCurrentBombNb(unsigned int value);
            void setVelocityLevel(unsigned int value);
            void setWallPass(bool value);

            void setBehavior(unsigned int value);
            unsigned int getBehavior() const;

        private:
            unsigned int bombsRange;
            unsigned int maxBombNb;
            unsigned int currentBombNb;
            unsigned int velocityLevel;
            bool wallPass;
            unsigned int behavior;
            std::string name;
    };
} // namespace Indie::Components

#endif /* !PLAYERCOMPONENT_HPP_ */
