/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** MasterInfo
*/

#ifndef MASTERINFO_HPP_
#define MASTERINFO_HPP_

#include <map>

namespace Indie
{
    struct MasterInfo {
        unsigned short int xp = 0;
        unsigned short int lvl = 0;
        std::map<std::string, int> scores_map = {};
    };
}

#endif /* !MASTERINFO_HPP_ */
