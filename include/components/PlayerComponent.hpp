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
                GREEN,
                BLUE,
                YELLOW,
                PURPLE,
                GENERIC,
            };

            enum class PLAYER_START_POSITION {
                TOP_LEFT,
                TOP_RIGHT,
                DOWN_LEFT,
                DOWN_RIGHT,
            };

        public:
            PlayerComponent(const std::string &playerNb, PLAYER_COLOR playerColor, PLAYER_START_POSITION startPosition);
            ~PlayerComponent() = default;

            unsigned int getBombsRange(void) const;
            unsigned int getMaxBombNb(void) const;
            unsigned int getCurrentBombNb(void) const;
            unsigned int getVelocityLevel(void) const;
            unsigned int getLevelCount(void) const;
            unsigned int getXpCount(void) const;
            bool getWallPass(void) const;
            bool isDead(void) const;
            const std::string &getName(void) const;
            PLAYER_COLOR getPlayerColor(void) const;
            PLAYER_START_POSITION getStartPosition(void) const;

            void setBombsRange(unsigned int value);
            void setMaxBombNb(unsigned int value);
            void setCurrentBombNb(unsigned int value);
            void setVelocityLevel(unsigned int value);
            void setLevelCount(unsigned int value);
            void setXpCount(unsigned int value);
            void setWallPass(bool value);
            void setIsDead(bool value);

            void setBehavior(unsigned int value);
            unsigned int getBehavior() const;

        private:
            unsigned int bombsRange;
            unsigned int maxBombNb;
            unsigned int currentBombNb;
            unsigned int velocityLevel;
            unsigned int level;
            unsigned int xp;
            bool wallPass;
            bool _isDead;
            unsigned int behavior;
            std::string name;
            PLAYER_COLOR playerColor;
            PLAYER_START_POSITION startPosition;
    };
} // namespace Indie::Components

#endif /* !PLAYERCOMPONENT_HPP_ */
