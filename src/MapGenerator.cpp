/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** MapGenerator
*/


#include "MapGenerator.hpp"

Indie::MapGenerator::MapGenerator(enum type type, enum theme theme, int x, int y)
{   
    setTheme(theme);
    setDimension(x, y);
    setType(type);
    for (int i = _y - 1; i >= 0; i--) {
        for (size_t j = 0; j < _x; j++) {
            if (i == 0 || j == 0 || i == _y - 1 || j == _x - 1)
                _map[i][j] = -1;
        }
        std::cout << std::endl;
    }
}

void Indie::MapGenerator::generate(EntityManager &entityManager, ContextManager &contextManager)
{
    int x = 0;
    int y = 0;

    std::string path = "../ressources/static_mesh/";

    if (_theme == DIRT)
        path = path + "map_dirt/";
    else
        path = path + "map_stone/";

    for (int i = _y - 1; i >= 0; i--) {
        for (size_t j = 0; j < _x; j++) {
            Indie::EntityBuilder::createGround(entityManager, irr::core::vector3df(x, 0, y), path + "ground.obj", path + "ground.png", contextManager);
            x += 20;
        }
        x = 0;
        y += 20;
    }
    for (int i = _y - 1; i >= 0; i--) {
        for (size_t j = 0; j < _x; j++) {
            if (_map[i][j] == -1)
                Indie::EntityBuilder::createGround(entityManager, irr::core::vector3df(20 * j, 20, 20 * i), path + "wall_side.obj", path + "wall_side.png", contextManager);
            else if (_map[i][j] == 1)
                Indie::EntityBuilder::createGround(entityManager, irr::core::vector3df(20 * j, 20, 20 * i), path + "box.obj", path + "box.png", contextManager);
            else if (_map[i][j] == 2)
                Indie::EntityBuilder::createGround(entityManager, irr::core::vector3df(20 * j, 20, 20 * i), path + "wall_middle.obj", path + "wall_middle.png", contextManager);
            else if (_map[i][j] == 3)
                Indie::EntityBuilder::createGround(entityManager, irr::core::vector3df(20 * j, 20, 20 * i), path + "ground.obj", "ground.png", contextManager);
        }
    }
}

void Indie::MapGenerator::setDimension(int x, int y)
{
    this->_y = y;
    this->_x = x;
    std::vector<std::vector<int> > matrix(_y);
    for (int i = 0 ; i < _y; i++)
        matrix[i].resize(_x);
    _map = matrix;
}

void Indie::MapGenerator::setType(enum type type)
{
    _type = type;
    if (type == DEFAULT)
        createDefaultMap();
    else if (type == RANDOM)
        createRandomMap(50, 50);
    else if (type == EMPTY)
        clearMap();
}

void Indie::MapGenerator::setTheme(enum theme theme)
{
    _theme = theme;
}

void Indie::MapGenerator::clearMap()
{
    for (size_t i = 1; i < _y - 1; i++) {
        for (size_t j = 1; j < _x - 1; j++) {
            _map[i][j];
        }
    }
}

void Indie::MapGenerator::createDefaultMap()
{
    for (size_t i = 1; i < _y - 1; i++) {
        for (size_t j = 1; j < _x - 1; j++) {
            if (_x % 2 == 1 || _y % 2 == 1) {
                if (j % 2 == 0 && i % 2 == 0)
                    _map[i][j] = IN_WALL;
                else
                    _map[i][j] = BOX;
            }
            else {
                if (j % 2 == 0 && i % 2 == 0 && i < _x - 2 && j < _y - 2)
                    _map[i][j] = IN_WALL;
                else
                    _map[i][j] = BOX;
            }
        }
    }
    this->setSpawn();
}

void Indie::MapGenerator::createRandomMap(int percentageBox, int percentageWall)
{
    std::srand(std::time(nullptr));
    int random = 0;

    for (size_t i = 1; i < _y - 1; i++) {
        for (size_t j = 1; j < _x - 1; j++) {
            random = 1 + std::rand()/((RAND_MAX + 1u) / 100);
            if (random <= percentageBox)
                _map[i][j] = BOX;
            else {
                random = 1 + std::rand()/((RAND_MAX + 1u) / 100);
                if (random <= percentageWall)
                    _map[i][j] = IN_WALL;
            }
        }
    }
    this->setSpawn();
}

void Indie::MapGenerator::setSpawn()
{
    _map[1][1] = VOID;
    _map[1][2] = VOID;
    _map[2][1] = VOID;
    _map[1][_x - 2] = VOID;
    _map[1][_x - 3] = VOID;
    _map[2][_x - 2] = VOID;
    _map[_y - 2][_x - 2] = VOID;
    _map[_y - 2][_x - 3] = VOID;
    _map[_y - 3][_x - 2] = VOID;
    _map[_y - 2][1] = VOID;
    _map[_y - 2][2] = VOID;
    _map[_y - 3][1] = VOID;
    if (_x >= 11  && _y >= 11) {
        _map[1][3] = VOID;
        _map[3][1] = VOID;
        _map[3][_x - 2] = VOID;
        _map[1][_x - 4] = VOID;
        _map[_y - 2][_x - 4] = VOID;
        _map[_y - 4][_x - 2] = VOID;
        _map[_y - 2][3] = VOID;
        _map[_y - 4][1] = VOID;
    }
}