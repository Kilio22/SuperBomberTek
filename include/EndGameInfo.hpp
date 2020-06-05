/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** EndGame
*/

#ifndef ENDGAME_HPP_
#define ENDGAME_HPP_

#include <vector>

namespace Indie
{
    enum class MATCH_PLAY {
        WIN,
        LOSE,
        DRAW,
        P1_WON,
        P2_WON,
        BOTH_LOSE
    };

    struct EndGame {
        std::vector<int> score = {};
        MATCH_PLAY matchPlay;
    };
}

#endif /* !ENDGAME_HPP_ */
