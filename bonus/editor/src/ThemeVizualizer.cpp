/*
** EPITECH PROJECT, 2019
** editor
** File description:
** ThemeVizualizer.cpp
*/

#include "ThemeVisualizer.hpp"
extern sf::View view;

ThemeVizualizer::ThemeVizualizer(EDITOR::THEME theme)
{
    _animId = 0;
    _theme = theme;
    _clock.restart();

    _lightTexture.loadFromFile("assets/bombertek.png", {50, 0, 32, 128});
    for (int i = 0; i < 4; i++) {
        _lightSprites[i].setTexture(_lightTexture);
        _lightSprites[i].setTextureRect({0, 32 * i, 32, 32});
    }

    _darkTexture.loadFromFile("assets/bombertek.png", {82, 0, 32, 128});
    for (int i = 0; i < 4; i++) {
        _darkSprites[i].setTexture(_darkTexture);
        _darkSprites[i].setTextureRect({0, i * 32, 31, 32});
    }

    _mountainTexture.loadFromFile("assets/bombertek.png", {113, 0, 32, 128});
    for (int i = 0; i < 4; i++) {
        _mountainSprite[i].setTexture(_mountainTexture);
        _mountainSprite[i].setTextureRect({0, 32 * i, 32, 32});
    }
}

ThemeVizualizer::~ThemeVizualizer() {

}

void ThemeVizualizer::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    states.transform *= getTransform();
    
    if (_theme == EDITOR::THEME::LIGHT)
        target.draw(_lightSprites[_animId], states);
    else if (_theme == EDITOR::THEME::DARK)
        target.draw(_darkSprites[_animId], states);
    else if (_theme == EDITOR::THEME::MOUNTAIN)
        target.draw(_mountainSprite[_animId], states);
}

void ThemeVizualizer::update() {
    sf::Time t = _clock.getElapsedTime();

    if (t > sf::milliseconds(150)) {
        _clock.restart();
        _animId++;
        if (_animId == 4)
            _animId = 0;
    }
}