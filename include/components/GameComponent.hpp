/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** GameComponent
*/

#ifndef GAMECOMPONENT_HPP_
#define GAMECOMPONENT_HPP_

#include "EndGameInfo.hpp"

namespace Indie::Components
{
    class GameComponent
    {
    public:
        GameComponent();
        ~GameComponent() = default;

        MATCH_PLAY getGameStatus() const;
        void setGameStatus(MATCH_PLAY status);

    private:
        MATCH_PLAY gameStatus;
    };
} // namespace Indie::Components

#endif /* !GAMECOMPONENT_HPP_ */
