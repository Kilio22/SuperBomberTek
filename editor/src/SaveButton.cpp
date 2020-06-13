/*
** EPITECH PROJECT, 2019
** editor
** File description:
** saveButton.cpp
*/

#include "SaveButton.hpp"

SaveButton::SaveButton() {
    _idleTexture.loadFromFile("assets/Save_idle.png");
    _hoveredTexture.loadFromFile("assets/Save_selected.png");
    _pressedTexture.loadFromFile("assets/Save_pressed.png");

    _idle.setTexture(_idleTexture);
    _hovered.setTexture(_hoveredTexture);
    _pressed.setTexture(_pressedTexture);

    _idle.setTextureRect((sf::IntRect){5, 5, 190, 32});
    _hovered.setTextureRect((sf::IntRect){5, 5, 190, 32});
    _pressed.setTextureRect((sf::IntRect){5, 5, 190, 32});
}

void SaveButton::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    states.transform *= getTransform();
    if (_clickedState) {
        target.draw(_pressed, states);
    } else if (_hoveredState) {
        target.draw(_hovered, states);
    } else {
        target.draw(_idle, states);
    }
}

void SaveButton::update(const sf::RenderWindow &window) {
    int mx = sf::Mouse::getPosition(window).x;
    int my = sf::Mouse::getPosition(window).y;

    if (isButtonClicked(mx, my)) {
        _clickedState = true;
        _hoveredState = false;
    } else if (isButtonHover(mx, my)) {
        _clickedState = false;
        _hoveredState = true;
    } else {
        _clickedState = false;
        _hoveredState = false;
    }
}

bool SaveButton::isButtonHover(int mx, int my) const {
sf::IntRect rect(
        getPosition().x,
        getPosition().y,
        _idle.getScale().x * 190,
        _idle.getScale().y * 32
    );
    
    return (mx >= rect.left && mx < rect.left + rect.width && my >= rect.top && my < rect.top + rect.height);
}

bool SaveButton::isButtonClicked(int mx, int my) const {
    return (sf::Mouse::isButtonPressed(sf::Mouse::Left) && isButtonHover(mx, my));
}