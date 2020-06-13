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

    _emptySelector.setPosition(517, 213);
    _destructibleSelector.setPosition(517, 180);
    _undestructibleSelector.setPosition(517, 147);

    _brushState = EDITOR::TILETYPE::EMPTY;
    _themeState = EDITOR::THEME::LIGHT;
    _lightSelector.setSelected(true);
    _emptySelector.setSelected(true);
}

Hud::~Hud() {

}

void Hud::draw(sf::RenderWindow &window) {
    window.draw(_placeholder);
    window.draw(_lightSelector);
    window.draw(_darkSelector);
    window.draw(_mountainSelector);
    window.draw(_emptySelector);
    window.draw(_destructibleSelector);
    window.draw(_undestructibleSelector);
}

void Hud::update(const sf::RenderWindow &window) {
    int mx = sf::Mouse::getPosition(window).x;
    int my = sf::Mouse::getPosition(window).y;

    _lightSelector.update(window);
    _darkSelector.update(window);
    _mountainSelector.update(window);
    _emptySelector.update(window);
    _destructibleSelector.update(window);
    _undestructibleSelector.update(window);
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

    if (_emptySelector.isButtonClicked(mx, my)) {
        _emptySelector.setSelected(false);
        _destructibleSelector.setSelected(false);
        _undestructibleSelector.setSelected(false);
        _emptySelector.setSelected(true);
        _brushState = EDITOR::TILETYPE::EMPTY;
    } else if (_destructibleSelector.isButtonClicked(mx, my)) {
        _emptySelector.setSelected(false);
        _destructibleSelector.setSelected(false);
        _undestructibleSelector.setSelected(false);
        _destructibleSelector.setSelected(true);
        _brushState = EDITOR::TILETYPE::DESTRUCTIBLE;
    } else if (_undestructibleSelector.isButtonClicked(mx, my)) {
        _emptySelector.setSelected(false);
        _destructibleSelector.setSelected(false);
        _undestructibleSelector.setSelected(false);
        _undestructibleSelector.setSelected(true);
        _brushState = EDITOR::TILETYPE::UNDESTRUCTIBLE;
    }
}