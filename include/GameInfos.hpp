/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** GameInfos
*/

#ifndef GAMEINFOS_HPP_
#define GAMEINFOS_HPP_

#include <unordered_map>
#include <vector>

namespace Indie
{
    struct GameInfos {
        unsigned int xp;
        unsigned int lvl;
        std::unordered_map<std::string, int> scores_map;
        static const std::vector<unsigned int> xp_level;
    };
}

#endif /* !GAMEINFOS_HPP_ */
