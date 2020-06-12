/*
** EPITECH PROJECT, 2019
** editor
** File description:
** Map.cpp
*/

#include "Map.hpp"

Map::Map() {
    for (int x = 0; x < 13; x++) {
        for (int y = 0; y < 11; y++)
            _tiles[x][y] = EMPTY;
    }

    _texture.loadFromFile("assets/bombertek.png");
}

Map::~Map() {

}

void Map::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    (void)states;
    sf::RectangleShape placeholder;

    placeholder.setPosition(10, 10);
    placeholder.setSize(sf::Vector2f(480, 416));
    placeholder.setFillColor(sf::Color::Red);
    target.draw(placeholder);

    for (int i = 0; i < 13; i++) {
        sf::RectangleShape placeholder;
        
        placeholder.setSize({32, 32});
        placeholder.setPosition(10, 10 + i * 32);
        placeholder.setFillColor(sf::Color::Blue);
        target.draw(placeholder);
    }
    for (int i = 0; i < 15; i++) {
        sf::RectangleShape placeholder;
        
        placeholder.setSize({32, 32});
        placeholder.setPosition(10 + i * 32, 10);
        placeholder.setFillColor(sf::Color::Blue);
        target.draw(placeholder);
    }
    for (int i = 0; i < 15; i++) {
        sf::RectangleShape placeholder;
        
        placeholder.setSize({32, 32});
        placeholder.setPosition(10 + i * 32, 10 + 32 * 12);
        placeholder.setFillColor(sf::Color::Blue);
        target.draw(placeholder);
    }
    for (int i = 0; i < 13; i++) {
        sf::RectangleShape placeholder;
        
        placeholder.setSize({32, 32});
        placeholder.setPosition(10 + 14 * 32, 10 + i * 32);
        placeholder.setFillColor(sf::Color::Blue);
        target.draw(placeholder);
    }
    for (int x = 0; x < 13; x++) {
        for (int y = 0; y < 15; y++) {
            switch (_tiles[x][y])
            {
            case TileType::UNDESTRUCTIBLE:

                break;
            case TileType::DESTRUCTIBLE:

                break;
            default:
                
                break;
            }
        }
    }
}