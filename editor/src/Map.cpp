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
            _tiles[x][y] = 0;
    }
}

Map::~Map() {

}