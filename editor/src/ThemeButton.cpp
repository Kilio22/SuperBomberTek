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
    _pressedState = false;

    switch (theme) {
        case EDITOR::THEME::LIGHT:
            _idleTexture.loadFromFile("assets/Dirt_idle.png");
            _selectedTexture.loadFromFile("assets/Dirt_selected.png");
            _pressedTexture.loadFromFile("assets/Dirt_pressed.png");
            _idle.setTexture(_idleTexture);
            _selected.setTexture(_selectedTexture);
            _pressed.setTexture(_pressedTexture);
            _idle.setTextureRect((sf::IntRect){68, 400, 64, 32});
            _selected.setTextureRect((sf::IntRect){68, 400, 64, 32});
            _pressed.setTextureRect((sf::IntRect){68, 400, 64, 32});
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

void ThemeButton::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    states.transform *= getTransform();
    if (_pressedState) {
        target.draw(_pressed, states);
     } else if (_selectedState) {
        target.draw(_selected, states);
    } else {
        target.draw(_idle, states);
    }
}

void ThemeButton::update(const sf::RenderWindow &window) {
    int mx = sf::Mouse::getPosition(window).x;
    int my = sf::Mouse::getPosition(window).y;

    if (isButtonClicked(mx, my))
        _pressedState = true;
    else 
        _pressedState = false;
}

bool ThemeButton::isButtonHover(int mx, int my) const {
    sf::IntRect rect(
        getPosition().x,
        getPosition().y,
        _idle.getScale().x * 64,
        _idle.getScale().y * 32
    );
    
    return (mx >= rect.left && mx < rect.left + rect.width && my >= rect.top && my < rect.top + rect.height);
}

bool ThemeButton::isButtonClicked(int mx, int my) const {
    return (sf::Mouse::isButtonPressed(sf::Mouse::Left) && isButtonHover(mx, my));
}