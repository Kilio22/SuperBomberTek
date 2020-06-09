/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** PlayerMaps
*/

#ifndef PLAYERMAPS_HPP_
#define PLAYERMAPS_HPP_

#include <vector>
#include <string>

namespace Indie
{
    class PlayerMaps
    {
    public:
        struct PlayerMap
        {
            std::string path;
            unsigned int reqLvl;
        };

    public:
        PlayerMaps() = default;
        ~PlayerMaps() = default;

        static const std::vector<PlayerMap> mapPaths;
    };
}

#endif /* !PLAYERMAPS_HPP_ */
