/*
** EPITECH PROJECT, 2019
** editor
** File description:
** BrushButton.cpp
*/

#include "BrushButton.hpp"

BrushButton::BrushButton() {
    _selectedState = false;
    _pressedState = false;

    _idleTexture.loadFromFile("assets/B1_idle.png");
    _pressedTexture.loadFromFile("assets/B1_pressed.png");
    _selectedTexture.loadFromFile("assets/B1_selected.png");

    _idle.setTexture(_idleTexture);
    _pressed.setTexture(_pressedTexture);
    _selected.setTexture(_selectedTexture);

    _idle.setTextureRect({18, 147, 32, 32});
    _pressed.setTextureRect({18, 147, 32, 32});
    _selected.setTextureRect({18, 147, 32, 32});
}

void BrushButton::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    states.transform *= getTransform();
    if (_pressedState) {
        target.draw(_pressed, states);
    } else if (_selectedState) {
        target.draw(_selected, states);
    } else {
        target.draw(_idle, states);
    }
}

void BrushButton::update(const sf::RenderWindow &window) {
    int mx = window.mapPixelToCoords(sf::Mouse::getPosition(window)).x;
    int my = window.mapPixelToCoords(sf::Mouse::getPosition(window)).y;

    if (isButtonClicked(mx, my))
        _pressedState = true;
    else 
        _pressedState = false;
}

bool BrushButton::isButtonHover(int mx, int my) const {
    sf::IntRect rect(
        getPosition().x,
        getPosition().y,
        _idle.getScale().x * 32,
        _idle.getScale().y * 32
    );
    
    return (mx >= rect.left && mx < rect.left + rect.width && my >= rect.top && my < rect.top + rect.height);
}

bool BrushButton::isButtonClicked(int mx, int my) const {
    return (sf::Mouse::isButtonPressed(sf::Mouse::Left) && isButtonHover(mx, my));
}