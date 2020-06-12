/*
** EPITECH PROJECT, 2019
** editor
** File description:
** BrushButton.cpp
*/

#include "BrushButton.hpp"

BrushButton::BrushButton(EDITOR::TILETYPE type) {
    _selectedState = false;
    _pressedState = false;

    switch (type)
    {
        case EDITOR::TILETYPE::EMPTY:

            break;
        case EDITOR::TILETYPE::DESTRUCTIBLE:
            break;
        case EDITOR::TILETYPE::UNDESTRUCTIBLE:
            break;
        default: break;
    }
}

void BrushButton::draw(sf::RenderTarget &target, sf::RenderStates states) const {

}

void BrushButton::update(sf::RenderWindow &window) {

}

bool BrushButton::isButtonHover(int mx, int my) const {

}

bool BrushButton::isButtonClicked(int mx, int my) const {
    
}