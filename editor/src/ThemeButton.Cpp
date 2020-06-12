/*
** EPITECH PROJECT, 2019
** editor
** File description:
** LargeButton.Cpp
*/

#include "ThemeButton.hpp"

ThemeButton::ThemeButton(EDITOR::THEME theme) {
    _theme = theme;
    _selectedState = false;

    switch (theme) {
        case EDITOR::THEME::LIGHT:
            _idleTexture.loadFromFile("assets/Dirt_idle.png");
            _selectedTexture.loadFromFile("assets/Dirt_selected.png");
            _pressedTexture.loadFromFile("assets/Dirt_pressed.png");
            _idle.setTexture(_idleTexture);
            _selected.setTexture(_selectedTexture);
            _pressed.setTexture(_pressedTexture);
            break;
        case EDITOR::THEME::DARK:
            _idleTexture.loadFromFile("assets/Stone_idle.png");
            _selectedTexture.loadFromFile("assets/Stone_selected.png");
            _pressedTexture.loadFromFile("assets/Stone_pressed.png");
            _idle.setTexture(_idleTexture);
            _selected.setTexture(_selectedTexture);
            _pressed.setTexture(_pressedTexture);
            break;
        case EDITOR::THEME::MOUNTAIN:
            _idleTexture.loadFromFile("assets/Snow idle.png");
            _selectedTexture.loadFromFile("assets/Snow selected.png");
            _pressedTexture.loadFromFile("assets/Snow pressed.png");
            _idle.setTexture(_idleTexture);
            _selected.setTexture(_selectedTexture);
            _pressed.setTexture(_pressedTexture);
            break;
        default: break;
    }
}