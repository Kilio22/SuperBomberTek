/*
** EPITECH PROJECT, 2019
** editor
** File description:
** ThemeVizualizer.cpp
*/

#include "ThemeVisualizer.hpp"

ThemeVizualizer::ThemeVizualizer(THEME theme)
{
    _animId = 0;
    _theme = theme;
    _clock.restart();

    _lightTexture.loadFromFile("assets/bombertek.png", (sf::IntRect){50, 6, 27, 115});
    for (int i = 0; i < 4; i++) {
        _lightSprites[i].setTexture(_lightTexture);
        _lightSprites[i].setTextureRect((sf::IntRect){0, 29 * i, 27, 29});
    }

    _darkTexture.loadFromFile("assets/bombertek.png", (sf::IntRect){82, 4, 29, 117});
    for (int i = 0; i < 4; i++) {
        _darkSprites[i].setTexture(_darkTexture);
        _darkSprites[i].setTextureRect((sf::IntRect){0, i * 29, 29, 29});
    }

    
}

ThemeVizualizer::~ThemeVizualizer() {

}

void ThemeVizualizer::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    states.transform *= getTransform();
    target.draw(_lightSprites[_animId], states);
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