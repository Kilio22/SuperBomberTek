/*
** EPITECH PROJECT, 2019
** editor
** File description:
** ModalSave.cpp
*/

#include "ModalSave.hpp"

ModalSave::ModalSave() {
    _layoutTexture.loadFromFile("assets/LayoutModal.png");
    _crossIdleTexture.loadFromFile("assets/Cross_idle.png");
    _crossSelectedTexture.loadFromFile("assets/Cross_selected.png");
    _crossPressedTexture.loadFromFile("assets/Cross_pressed.png");
    _saveIdleTexture.loadFromFile("assets/ModalSave_idle.png");
    _saveSelectedTexture.loadFromFile("assets/ModalSave_selected.png");
    _savePressedTexture.loadFromFile("assets/ModalSave_pressed.png");

    _layout.setTexture(_layoutTexture);
    _crossIdle.setTexture(_crossIdleTexture);
    _crossSelected.setTexture(_crossSelectedTexture);
    _crossPressed.setTexture(_crossPressedTexture);
    _saveIdle.setTexture(_saveIdleTexture);
    _saveSelected.setTexture(_saveSelectedTexture);
    _savePressed.setTexture(_savePressedTexture);

    _font.loadFromFile("assets/upheavtt.ttf");
}

void ModalSave::draw(sf::RenderWindow &window) const {
    sf::RectangleShape background;

    background.setFillColor(sf::Color(0, 0, 0, 150));
    background.setSize(sf::Vector2f{700, 436});
    window.draw(background);
    window.draw(_layout);

    if (isClosePressed(window)) {
        window.draw(_crossPressed);
    } else if (isCloseHovered(window)) {
        window.draw(_crossSelected);
    } else {
        window.draw(_crossIdle);
    }
    if (isSavePressed(window)) {
        window.draw(_savePressed);
    } else if (isSaveHovered(window)) {
        window.draw(_saveSelected);
    } else {
        window.draw(_saveIdle);
    }

    sf::Text input;
    input.setFont(_font);
    input.setString(_fileState);
    input.setFillColor(sf::Color::White);
    input.setPosition((sf::Vector2f){200, 150});
    window.draw(input);
}

bool ModalSave::isCloseHovered(const sf::RenderWindow &window) const {
    int mx = sf::Mouse::getPosition(window).x;
    int my = sf::Mouse::getPosition(window).y;
    sf::IntRect rect(554, 77, 42, 37);
    
    return (mx >= rect.left && mx < rect.left + rect.width && my >= rect.top && my < rect.top + rect.height);
}

bool ModalSave::isClosePressed(const sf::RenderWindow &window) const {
    return (sf::Mouse::isButtonPressed(sf::Mouse::Left) && isCloseHovered(window));
}

bool ModalSave::isSaveHovered(const sf::RenderWindow &window) const {
    int mx = sf::Mouse::getPosition(window).x;
    int my = sf::Mouse::getPosition(window).y;
    sf::IntRect rect(207, 207, 286, 42);
    
    return (mx >= rect.left && mx < rect.left + rect.width && my >= rect.top && my < rect.top + rect.height);
}

bool ModalSave::isSavePressed(const sf::RenderWindow &window) const {
    return (sf::Mouse::isButtonPressed(sf::Mouse::Left) && isSaveHovered(window));
}