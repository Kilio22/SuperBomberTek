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
    int mx = sf::Mouse::getPosition(window).x;
    int my = sf::Mouse::getPosition(window).y;

    _lightSelector.update(window);
    _darkSelector.update(window);
    _mountainSelector.update(window);

    if (_lightSelector.isButtonClicked(mx, my)) {
        _lightSelector.setSelected(false);
        _darkSelector.setSelected(false);
        _mountainSelector.setSelected(false);
        _lightSelector.setSelected(true);
        _themeState = EDITOR::THEME::LIGHT;
    } else if (_darkSelector.isButtonClicked(mx, my)) {
        _lightSelector.setSelected(false);
        _darkSelector.setSelected(false);
        _mountainSelector.setSelected(false);
        _darkSelector.setSelected(true);
        _themeState = EDITOR::THEME::DARK;
    } else if (_mountainSelector.isButtonClicked(mx, my)) {
        _lightSelector.setSelected(false);
        _darkSelector.setSelected(false);
        _mountainSelector.setSelected(false);
        _mountainSelector.setSelected(true);
        _themeState = EDITOR::THEME::MOUNTAIN;
    }
}