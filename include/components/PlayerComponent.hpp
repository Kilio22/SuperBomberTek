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
    /**
     * @brief Player component
     */
    class PlayerComponent
    {
    public:
        enum class PLAYER_COLOR
        {
            RED = 0,
            GREEN = 1,
            BLUE = 2,
            YELLOW = 3,
            PURPLE = 4,
            GREY = 5,
        };

        enum class PLAYER_START_POSITION
        {
            TOP_LEFT = 0,
            TOP_RIGHT = 1,
            DOWN_LEFT = 2,
            DOWN_RIGHT = 3,
        };

    public:
        PlayerComponent(const std::string &name, PLAYER_COLOR playerColor, PLAYER_START_POSITION startPosition, bool isHuman);
        ~PlayerComponent() = default;

        /**
         * @brief Used to check if entity is linked to a human player
         * @return true Player is a human player
         * @return false Player is not a human player
         */
        bool isHuman(void) const;

        /**
         * @brief Gets bombs range
         * @return unsigned int Bombs range
         */
        unsigned int getBombsRange(void) const;

        /**
         * @brief Gets the maximum number of bombs that can be dropped simultaneously
         * @return unsigned int The number
         */
        unsigned int getMaxBombNb(void) const;

        /**
         * @brief Gets the current number of bombs that can be dropped
         * @return unsigned int The number
         */
        unsigned int getCurrentBombNb(void) const;

        /**
         * @brief Gets the velocity level of the player
         * @return unsigned int The level
         */
        unsigned int getVelocityLevel(void) const;

        /**
         * @brief Gets the XP count
         * @return unsigned int The XP count
         */
        unsigned int getXp(void) const;

        /**
         * @brief Gets the score value
         * @return int The score value
         */
        int getScore(void) const;

        /**
         * @brief Gets wall pass boolean value in order to check if the player took this power up
         * @return true The player took the power up
         * @return false The player didn't took the power up
         */
        bool getWallPass(void) const;

        /**
         * @brief Gets the player's state : dead or alive
         * @return true The player is dead
         * @return false The player is alive
         */
        bool isDead(void) const;

        /**
         * @brief Gets the player's name
         * @return const std::string& The name
         */
        const std::string &getName(void) const;

        /**
         * @brief Gets the player's color
         * @return PLAYER_COLOR The color
         */
        PLAYER_COLOR getPlayerColor(void) const;

        /**
         * @brief Gets the player's start position
         * @return PLAYER_START_POSITION The start position
         */
        PLAYER_START_POSITION getStartPosition(void) const;

        /**
         * @brief Sets bombs range
         * @param value The new range
         */
        void setBombsRange(unsigned int value);

        /**
         * @brief Sets the maximum number of bombs that can be dropped simultaneously
         * @param value The new the maximum number of bombs that can be dropped simultaneously
         */
        void setMaxBombNb(unsigned int value);

        /**
         * @brief Sets the current number of bombs that can be dropped
         * @param value The new number
         */
        void setCurrentBombNb(unsigned int value);

        /**
         * @brief Sets the velocity level
         * @param value The new leven
         */
        void setVelocityLevel(unsigned int value);

        /**
         * @brief Sets the XP count
         * @param value The new XP count
         */
        void setXpCount(unsigned int value);

        /**
         * @brief Sets the score value
         * @param score The score value
         */
        void setScore(int score);

        /**
         * @brief Sets wall pass boolean value
         * @param value The new value
         */
        void setWallPass(bool value);

        /**
         * @brief Sets the player's state
         * @param value The new state
         */
        void setIsDead(bool value);

    private:
        bool _isHuman;
        unsigned int bombsRange;
        unsigned int maxBombNb;
        unsigned int currentBombNb;
        unsigned int velocityLevel;
        unsigned int xp;
        int score;
        bool wallPass;
        bool _isDead;
        std::string name;
        PLAYER_COLOR playerColor;
        PLAYER_START_POSITION startPosition;
    };
} // namespace Indie::Components

#endif /* !PLAYERCOMPONENT_HPP_ */
