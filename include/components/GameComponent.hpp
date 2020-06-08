/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** GameComponent
*/

#ifndef GAMECOMPONENT_HPP_
#define GAMECOMPONENT_HPP_

#include <irrlicht.h>
#include "EndGameInfo.hpp"

namespace Indie::Components
{
    class GameComponent
    {
    public:
        GameComponent(irr::f32 timeToEnd);
        ~GameComponent() = default;

        MATCH_PLAY getGameStatus() const;
        void setGameStatus(MATCH_PLAY status);
        irr::f32 getTimeToEnd(void) const;
        void setTimeToEnd(irr::f32 value);

    private:
        MATCH_PLAY gameStatus;
        irr::f32 timeToEnd;
    };
} // namespace Indie::Components

#endif /* !GAMECOMPONENT_HPP_ */
