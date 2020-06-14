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
        _darkThemeSprite[i].setTextureRect({0, 32 * i, 16, 32});
        _lightThemeSprite[i].setTextureRect({16, 32 * i, 16, 32});
        _mountainSprite[i].setTextureRect({32, 32 * i, 16, 32});
    }
    _cursor.setTexture(_texture);
    _cursor.setTextureRect({0, 8 * 16, 16, 32});
    _cursor.setScale(2, 2);
}

Map::~Map() {

}

void Map::draw(sf::RenderWindow &target) {
    sf::Sprite externalWall = _currentTheme == EDITOR::LIGHT ? _lightThemeSprite[0] : _currentTheme == EDITOR::DARK ? _darkThemeSprite[0] : _mountainSprite[0];
    sf::Sprite destructibleWall = _currentTheme == EDITOR::LIGHT ? _lightThemeSprite[1] : _currentTheme == EDITOR::DARK ? _darkThemeSprite[1] : _mountainSprite[1];
    sf::Sprite undestructibleWall = _currentTheme == EDITOR::LIGHT ? _lightThemeSprite[2] : _currentTheme == EDITOR::DARK ? _darkThemeSprite[2] : _mountainSprite[2];
    sf::Sprite ground = _currentTheme == EDITOR::LIGHT ? _lightThemeSprite[3] : _currentTheme == EDITOR::DARK ? _darkThemeSprite[3] : _mountainSprite[3];

    int mx = target.mapPixelToCoords(sf::Mouse::getPosition(target)).x;
    int my = target.mapPixelToCoords(sf::Mouse::getPosition(target)).y;
    for (int x = 0; x < 13; x++) {
        for (int y = 0; y < 11; y++) {
            ground.setScale(2, 2);
            ground.setPosition(10 + 32 + x * 32, 10 + 32 + y * 32);
            target.draw(ground);

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
            sf::IntRect tile = {10 + 32 + x * 32, 10 + 32 + y * 32, 32, 32};
            if (mx >= tile.left && mx < tile.left + tile.width && my >= tile.top && my < tile.top + tile.height) {
                _cursor.setPosition(10 + 32 + x * 32, 10 + y * 32);
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

    int mx = target.mapPixelToCoords(sf::Mouse::getPosition(target)).x;
    int my = target.mapPixelToCoords(sf::Mouse::getPosition(target)).y;
    if (_currentBrush == EDITOR::TILETYPE::EMPTY)
        _cursor.setTextureRect({32, 8 * 16, 16, 32});
    else if (_currentBrush == EDITOR::TILETYPE::DESTRUCTIBLE)
        _cursor.setTextureRect({16, 8 * 16, 16, 32});
    else
        _cursor.setTextureRect({0, 8 * 16, 16, 32});

    for (int x = 0; x < 13; x++) {
        for (int y = 0; y < 11; y++) {
            sf::IntRect tile = {10 + 32 + x * 32, 10 + 64 + y * 32, 32, 32};
            if (mx >= tile.left && mx < tile.left + tile.width && my >= tile.top && my < tile.top + tile.height) {
                if (x == 0 && y == 0)
                    break;
                if (x == 12 && y == 0)
                    break;
                if (x == 0 && y == 10)
                    break;
                if (x == 12 && y == 10)
                    break;
                _tiles[x][y] = _currentBrush;
            }
        }
    }
}

void Map::save(const std::string &filename) {
    std::string definitiveFilename = filename + ".supermap";
    std::string toWrite = "-1 -1 -1 -1 -1 -1 -1 -1 -1 -1 -1 -1 -1 -1 -1\n";
    std::fstream file;

    for (int i = 0; i < 11; i++) {
        toWrite += "-1";
        for (int j = 0; j < 13; j++) {
            if (_tiles[j][i] == EDITOR::TILETYPE::EMPTY)
                toWrite += " 0";
            else if (_tiles[j][i] == EDITOR::TILETYPE::UNDESTRUCTIBLE)
                toWrite += " 1";
            else
                toWrite += " 2";
        }
        toWrite += " -1\n";
    }
    toWrite += "-1 -1 -1 -1 -1 -1 -1 -1 -1 -1 -1 -1 -1 -1 -1";
    file.open(definitiveFilename, std::ios::trunc | std::ios::out);
    file << toWrite;
    file.close();
}