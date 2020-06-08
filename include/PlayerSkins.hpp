/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** PlayerSkins
*/

#ifndef PLAYERSKINS_HPP_
#define PLAYERSKINS_HPP_

#include "PlayerComponent.hpp"
#include <string>
#include <vector>

namespace Indie
{
    class PlayerSkins
    {
    public:
        struct PlayerSkin
        {
            std::string path;
            Components::PlayerComponent::PLAYER_COLOR color;
            unsigned int reqLvl;
        };

    public:
        PlayerSkins() = default;
        ~PlayerSkins() = default;

        static const std::vector<PlayerSkin> skinPaths;
    };
}

#endif /* !PLAYERSKINS_HPP_ */
