/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** EndGame
*/

#ifndef ENDGAME_HPP_
#define ENDGAME_HPP_

#include <string>
#include <vector>

namespace Indie
{
    enum class MATCH_PLAY {
        NOT_ENDED = 0,
        WIN = 1,
        LOSE = 2,
        DRAW = 3,
    };

    struct EndGame {
        std::vector<std::pair<std::string, int>> scores;
        unsigned int xp;
        MATCH_PLAY matchPlay;
    };
}

#endif /* !ENDGAME_HPP_ */
