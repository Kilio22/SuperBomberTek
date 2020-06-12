/*
** EPITECH PROJECT, 2019
** editor
** File description:
** Hud.cpp
*/

#include "Hud.hpp"

Hud::Hud() :
    _lightSelector(EDITOR::THEME::LIGHT),
    _darkSelector(EDITOR::THEME::DARK),
    _mountainSelector(EDITOR::THEME::MOUNTAIN)
{
    _brushState = EDITOR::TILETYPE::EMPTY;
    _themeState = EDITOR::THEME::LIGHT;
    _placeholerTexture.loadFromFile("assets/Layout.png");
    _placeholder.setTexture(_placeholerTexture);

    _placeholder.setPosition(500, 0);
    _lightSelector.setPosition(510, 400);
    _darkSelector.setPosition(575, 400);
    _mountainSelector.setPosition(633, 400);
}

Hud::~Hud() {

}

void Hud::draw(sf::RenderWindow &window) {
    window.draw(_placeholder);
    window.draw(_lightSelector);
    window.draw(_darkSelector);
    window.draw(_mountainSelector);
}

void Hud::update(const sf::RenderWindow &window) {
    _lightSelector.update(window);
    _darkSelector.update(window);
    _mountainSelector.update(window);
}