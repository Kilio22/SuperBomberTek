/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** MapGenerator
*/

#include <cstdlib>
#include <iostream>
#include <ctime>
#include "MapGenerator.hpp"

Indie::MapGenerator::MapGenerator(enum type_map type)
{
    for (size_t i = 0; i < 15; i++) {
        if (i == 0 || i == 14)
            _map.push_back({-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1});
        else
            _map.push_back({-1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -1});
    }
    if (type == DEFAULT)
        createDefaultMap();
    else if (type == RANDOM)
        createRandomMap();
}

Indie::MapGenerator::~MapGenerator()
{

}

void Indie::MapGenerator::createDefaultMap()
{
    for (size_t i = 1; i < 14; i++) {
        for (size_t j = 1; j < 14; j++) {
            if (j % 2 == 0 && i % 2 == 0)
                _map[i][j] = IN_WALL;
            else
                _map[i][j] = BOX;
        }
    }
    this->setSpawn();
}

void Indie::MapGenerator::createRandomMap()
{
    std::srand(std::time(nullptr));
    int random = 0;

    for (size_t i = 1; i < 14; i++) {
        for (size_t j = 1; j < 14; j++) {
            random = 1 + std::rand()/((RAND_MAX + 1u) / 2);
            if (random % 2 == 0) {
                _map[i][j] = BOX;
            }
            else {
                random = 1 + std::rand()/((RAND_MAX + 1u) / 3);
                if (random % 3 == 0)
                    _map[i][j] = IN_WALL;
            }
        }
    }
    this->setSpawn();
}

std::vector<std::vector<int>> Indie::MapGenerator::getMap()
{
    return this->_map;
}

void Indie::MapGenerator::setSpawn()
{
    _map[1][1] = EMPTY;
    _map[1][2] = EMPTY;
    _map[1][3] = EMPTY;
    _map[2][1] = EMPTY;
    _map[3][1] = EMPTY;
    _map[1][13] = EMPTY;
    _map[1][12] = EMPTY;
    _map[1][11] = EMPTY;
    _map[2][13] = EMPTY;
    _map[3][13] = EMPTY;
    _map[13][13] = EMPTY;
    _map[13][12] = EMPTY;
    _map[13][11] = EMPTY;
    _map[11][13] = EMPTY;
    _map[12][13] = EMPTY;
    _map[13][1] = EMPTY;
    _map[13][2] = EMPTY;
    _map[13][3] = EMPTY;
    _map[11][1] = EMPTY;
    _map[12][1] = EMPTY;
}