/*
** EPITECH PROJECT, 2019
** editor
** File description:
** Hud.cpp
*/

#include "Hud.hpp"

Hud::Hud() {
    _brushState = EMPTY;
}

Hud::~Hud() {

}

void Hud::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    (void)states;
    sf::RectangleShape placeholder;

    placeholder.setPosition(436, 0);
    placeholder.setSize(sf::Vector2f(200, 500));
    placeholder.setFillColor(sf::Color::Red);
    target.draw(placeholder);
}

void Hud::update(const sf::RenderWindow &window) {
    (void)window;
}