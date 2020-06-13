/*
** EPITECH PROJECT, 2019
** editor
** File description:
** ModalSave.cpp
*/

#include "ModalSave.hpp"

ModalSave::ModalSave() {
    _layoutTexture.loadFromFile("assets/LayoutModal.png");
    _layout.setTexture(_layoutTexture);
}

void ModalSave::draw(sf::RenderWindow &window) const {
    sf::RectangleShape background;

    background.setFillColor(sf::Color(0, 0, 0, 100));
    background.setSize(sf::Vector2f{700, 436});
    window.draw(background);
    window.draw(_layout);
}

void ModalSave::update(sf::RenderWindow &window) {

}

bool ModalSave::isCloseHovered(const sf::RenderWindow &window) {

}

bool ModalSave::isClosePressed(const sf::RenderWindow &window) {

}

bool ModalSave::isSaveHovered(const sf::RenderWindow &window) {

}

bool ModalSave::isSavePressed(const sf::RenderWindow &window) {

}