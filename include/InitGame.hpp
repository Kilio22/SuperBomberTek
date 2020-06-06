/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** GameInit | Author: Kylian BALAN - kylian.balan@epitech.eu
*/

#ifndef GAMEINIT_HPP_
#define GAMEINIT_HPP_

#include "GameScene.hpp"
#include "MapGenerator.hpp"
#include "PlayerComponent.hpp"
#include <irrlicht.h>
#include <map>
#include <string>
#include <vector>

namespace Indie
{
    struct PlayerParams {
        std::string playerTexture;
        std::map<irr::EKEY_CODE, Indie::Components::KEY_TYPE> playerKeys;
        Components::PlayerComponent::PLAYER_COLOR playerColor;
    };

    struct InitGame {
        Indie::GameScene::MODE mode = Indie::GameScene::MODE::SOLO;
        int nbAi = 0;
        Components::THEME mapTheme = Components::THEME::DIRT;
        Components::MAP_TYPE mapType = Components::MAP_TYPE::DEFAULT;
        bool powerUp = false;
        std::string mapPath = "";
        time_t timeLimit = 0;
        std::vector<PlayerParams> playersParams = {};
    };
} // namespace Indie

#endif /* !GAMEINIT_HPP_ */
