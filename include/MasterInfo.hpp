/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** MasterInfo
*/

#ifndef MASTERINFO_HPP_
#define MASTERINFO_HPP_

#include <unordered_map>
#include <vector>

namespace Indie
{
    struct MasterInfo {
        unsigned int xp;
        unsigned int lvl;
        std::unordered_map<std::string, int> scores_map;
        static const std::vector<unsigned int> xp_level;
    };
}

#endif /* !MASTERINFO_HPP_ */
