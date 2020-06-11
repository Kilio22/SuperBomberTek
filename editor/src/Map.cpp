/*
** EPITECH PROJECT, 2019
** editor
** File description:
** Map.cpp
*/

#include "Map.hpp"

Map::Map() {
    for (int x = 0; x < 13; x++) {
        for (int y = 0; y < 15; y++)
            _tiles[x][y] = EMPTY;
    }
}

Map::~Map() {

}

void Map::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    (void)states;
    sf::RectangleShape placeholder;

    placeholder.setPosition(10, 10);
    placeholder.setSize(sf::Vector2f(416, 480));
    placeholder.setFillColor(sf::Color::Red);
    target.draw(placeholder);
}