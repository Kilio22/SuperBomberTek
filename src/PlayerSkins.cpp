/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** PlayerSkins
*/

#include "PlayerSkins.hpp"

const std::vector<Indie::PlayerSkins::PlayerSkin> Indie::PlayerSkins::skinPaths {
    { "../ressources/textures/character/Gris.png", Components::PlayerComponent::PLAYER_COLOR::GENERIC, 0U },
    { "../ressources/textures/character/Bleu.png", Components::PlayerComponent::PLAYER_COLOR::BLUE, 0U },
    { "../ressources/textures/character/Rouge.png", Components::PlayerComponent::PLAYER_COLOR::RED, 0U },
    { "../ressources/textures/character/Vert.png", Components::PlayerComponent::PLAYER_COLOR::GREEN, 1U },
    { "../ressources/textures/character/Violet.png", Components::PlayerComponent::PLAYER_COLOR::PURPLE, 3U },
    { "../ressources/textures/character/Jaune.png", Components::PlayerComponent::PLAYER_COLOR::YELLOW, 5U },
    { "../ressources/textures/character/Gris+.png", Components::PlayerComponent::PLAYER_COLOR::GENERIC, 7U },
    { "../ressources/textures/character/Bleu+.png", Components::PlayerComponent::PLAYER_COLOR::BLUE, 9U },
    { "../ressources/textures/character/Rouge+.png", Components::PlayerComponent::PLAYER_COLOR::RED, 11U },
    { "../ressources/textures/character/Vert+.png", Components::PlayerComponent::PLAYER_COLOR::GREEN, 12U },
    { "../ressources/textures/character/Violet+.png", Components::PlayerComponent::PLAYER_COLOR::PURPLE, 13U },
    { "../ressources/textures/character/Jaune+.png", Components::PlayerComponent::PLAYER_COLOR::YELLOW, 14U },
};
