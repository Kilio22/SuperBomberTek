/*
** EPITECH PROJECT, 2019
** editor
** File description:
** Map.cpp
*/

#include "Map.hpp"

Map::Map(EDITOR::THEME theme) {
    _currentTheme = theme;
    _currentBrush = EDITOR::TILETYPE::EMPTY;

    for (int x = 0; x < 13; x++) {
        for (int y = 0; y < 11; y++)
            _tiles[x][y] = EDITOR::TILETYPE::EMPTY;
    }

    _texture.loadFromFile("assets/bombertek.png");
    for (int i = 0; i < 4; i++) {
        _lightThemeSprite[i].setTexture(_texture);
        _darkThemeSprite[i].setTexture(_texture);
        _mountainSprite[i].setTexture(_texture);
        _darkThemeSprite[i].setTextureRect((sf::IntRect){0, 32 * i, 16, 32});
        _lightThemeSprite[i].setTextureRect((sf::IntRect){16, 32 * i, 16, 32});
        _mountainSprite[i].setTextureRect((sf::IntRect){32, 32 * i, 16, 32});
    }
    _cursor.setTexture(_texture);
    _cursor.setTextureRect((sf::IntRect){0, 8 * 16, 16, 32});
    _cursor.setScale(2, 2);
}

Map::~Map() {

}

void Map::draw(sf::RenderWindow &target) {
    sf::Sprite externalWall = _currentTheme == EDITOR::LIGHT ? _lightThemeSprite[0] : _currentTheme == EDITOR::DARK ? _darkThemeSprite[0] : _mountainSprite[0];
    sf::Sprite destructibleWall = _currentTheme == EDITOR::LIGHT ? _lightThemeSprite[1] : _currentTheme == EDITOR::DARK ? _darkThemeSprite[1] : _mountainSprite[1];
    sf::Sprite undestructibleWall = _currentTheme == EDITOR::LIGHT ? _lightThemeSprite[2] : _currentTheme == EDITOR::DARK ? _darkThemeSprite[2] : _mountainSprite[2];
    sf::Sprite ground = _currentTheme == EDITOR::LIGHT ? _lightThemeSprite[3] : _currentTheme == EDITOR::DARK ? _darkThemeSprite[3] : _mountainSprite[3];

    int mx = sf::Mouse::getPosition(target).x;
    int my = sf::Mouse::getPosition(target).y;
    for (int x = 0; x < 13; x++) {
        for (int y = 0; y < 11; y++) {
            switch (_tiles[x][y]) {
                case EDITOR::TILETYPE::EMPTY:
                    ground.setScale(2, 2);
                    ground.setPosition(10 + 32 + x * 32, 10 + 32 + y * 32);
                    target.draw(ground);
                    break;
                default:break;
            }
        }
    }
    for (int x = 0; x < 13; x++) {
        for (int y = 0; y < 11; y++) {
            switch (_tiles[x][y]) {
                case EDITOR::TILETYPE::UNDESTRUCTIBLE:
                    undestructibleWall.setScale(2, 2);
                    undestructibleWall.setPosition(10 + 32 + x * 32, 10 + 32 + y * 32);
                    target.draw(undestructibleWall);
                    break;
                case EDITOR::TILETYPE::DESTRUCTIBLE:
                    destructibleWall.setScale(2, 2);
                    destructibleWall.setPosition(10 + 32 + x * 32, 10 + 32 + y * 32);
                    target.draw(destructibleWall);
                    break;
                default:break;
            }
        }
    }
    for (int x = 0; x < 13; x++) {
        for (int y = 0; y < 11; y++) {
            sf::IntRect tile = (sf::IntRect){10 + 32 + x * 32, 10 + 32 + y * 32, 32, 32};
            if (mx >= tile.left && mx < tile.left + tile.width && my >= tile.top && my < tile.top + tile.height) {
                _cursor.setPosition(10 + 32 + x * 32, 10 + 32 + y * 32);
                target.draw(_cursor);
            }
        }
    }
    for (int i = 0; i < 15; i++) {
        externalWall.setScale(2, 1);
        externalWall.setPosition(10 + i * 32, 10);
        target.draw(externalWall);
    }
    for (int i = 0; i < 12; i++) {
        externalWall.setScale(2, 2);
        externalWall.setPosition(10, 10 + i * 32);
        target.draw(externalWall);
    }
    for (int i = 0; i < 12; i++) {
        externalWall.setScale(2, 2);
        externalWall.setPosition(10 + 14 * 32, 10 + i * 32);
        target.draw(externalWall);
    }
    for (int i = 0; i < 15; i++) {
        externalWall.setScale(2, 1);
        externalWall.setPosition(10 + i * 32, 10 + 32 * 12);
        target.draw(externalWall);
    }
}

void Map::update(sf::RenderWindow &target) {
    if (!sf::Mouse::isButtonPressed(sf::Mouse::Left))
        return;

    int mx = sf::Mouse::getPosition(target).x;
    int my = sf::Mouse::getPosition(target).y;

    for (int x = 0; x < 13; x++) {
        for (int y = 0; y < 11; y++) {
            sf::IntRect tile = (sf::IntRect){10 + 32 + x * 32, 10 + 32 + y * 32, 32, 32};
            if (mx >= tile.left && mx < tile.left + tile.width && my >= tile.top && my < tile.top + tile.height) {
                _tiles[x][y] = _currentBrush;
            }
        }
    }
}