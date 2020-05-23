/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** MapGenerator
*/


#include "MapGenerator.hpp"

Indie::MapGenerator::MapGenerator(MAP_TYPE type, THEME theme, int x, int y)
{
    setTheme(theme);
    setDimension(x, y);
    setType(type);
    for (int i = _y - 1; i >= 0; i--) {
        for (int j = 0; j < _x; j++) {
            if (i == 0 || j == 0 || i == _y - 1 || j == _x - 1)
                _map[i][j] = -1;
        }
    }
}

void Indie::MapGenerator::generate(EntityManager &entityManager, ContextManager &contextManager)
{
    std::string path = "../ressources/static_mesh/";

    if (_theme == THEME::DIRT)
        path = path + "map_dirt/";
    else
        path = path + "map_stone/";
    for (int i = _y - 1; i >= 0; i--) {
        for (int j = 0; j < _x; j++) {
            Indie::EntityBuilder::createGround(entityManager, irr::core::vector3df((irr::f32)(20 * j), 0, (irr::f32)(20 * i)), path + "ground.obj", path + "ground.png", contextManager);
            if (_map[i][j] == -1)
                Indie::EntityBuilder::createWall(entityManager, irr::core::vector3df((irr::f32)(20 * j), 20, (irr::f32)(20 * i)), path + "wall_side.obj", path + "wall_side.png", contextManager, false);
            else if (_map[i][j] == 1)
                Indie::EntityBuilder::createWall(entityManager, irr::core::vector3df((irr::f32)(20 * j), 20, (irr::f32)(20 * i)), path + "box.obj", path + "box.png", contextManager, false);
            else if (_map[i][j] == 2)
                Indie::EntityBuilder::createWall(entityManager, irr::core::vector3df((irr::f32)(20 * j), 20, (irr::f32)(20 * i)), path + "wall_middle.obj", path + "wall_middle.png", contextManager, false);
            else if (_map[i][j] == 3)
                Indie::EntityBuilder::createWall(entityManager, irr::core::vector3df((irr::f32)(20 * j), 20, (irr::f32)(20 * i)), path + "ground.obj", "ground.png", contextManager, false);
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

void Indie::MapGenerator::setType(MAP_TYPE type)
{
    _type = type;
    if (type == MAP_TYPE::DEFAULT)
        createDefaultMap();
    else if (type == MAP_TYPE::RANDOM)
        createRandomMap(50, 50);
    else if (type == MAP_TYPE::EMPTY)
        clearMap();
}

void Indie::MapGenerator::setTheme(THEME theme)
{
    _theme = theme;
}

void Indie::MapGenerator::clearMap()
{
    for (int i = 1; i < _y - 1; i++) {
        for (int j = 1; j < _x - 1; j++) {
            _map[i][j] = -1;
        }
    }
}

void Indie::MapGenerator::createDefaultMap()
{
    for (int i = 1; i < _y - 1; i++) {
        for (int j = 1; j < _x - 1; j++) {
            if (_x % 2 == 1 || _y % 2 == 1) {
                if (j % 2 == 0 && i % 2 == 0)
                    _map[i][j] = (int)OBJECT::IN_WALL;
                else
                    _map[i][j] = (int)OBJECT::BOX;
            }
            else {
                if (j % 2 == 0 && i % 2 == 0 && i < _x - 2 && j < _y - 2)
                    _map[i][j] = (int)OBJECT::IN_WALL;
                else
                    _map[i][j] = (int)OBJECT::BOX;
            }
        }
    }
    this->setSpawn();
}

void Indie::MapGenerator::createRandomMap(int percentageBox, int percentageWall)
{
    std::srand((unsigned int)std::time(nullptr));
    int random = 0;

    for (int i = 1; i < _y - 1; i++) {
        for (int j = 1; j < _x - 1; j++) {
            random = 1 + std::rand()/((RAND_MAX + 1u) / 100);
            if (random <= percentageBox)
                _map[i][j] = (int)OBJECT::BOX;
            else {
                random = 1 + std::rand()/((RAND_MAX + 1u) / 100);
                if (random <= percentageWall)
                    _map[i][j] = (int)OBJECT::IN_WALL;
            }
        }
    }
    this->setSpawn();
}

void Indie::MapGenerator::setSpawn()
{
    _map[1][1] = (int)OBJECT::VOID;
    _map[1][2] = (int)OBJECT::VOID;
    _map[2][1] = (int)OBJECT::VOID;
    _map[1][_x - 2] = (int)OBJECT::VOID;
    _map[1][_x - 3] = (int)OBJECT::VOID;
    _map[2][_x - 2] = (int)OBJECT::VOID;
    _map[_y - 2][_x - 2] = (int)OBJECT::VOID;
    _map[_y - 2][_x - 3] = (int)OBJECT::VOID;
    _map[_y - 3][_x - 2] = (int)OBJECT::VOID;
    _map[_y - 2][1] = (int)OBJECT::VOID;
    _map[_y - 2][2] = (int)OBJECT::VOID;
    _map[_y - 3][1] = (int)OBJECT::VOID;
    if (_x >= 11  && _y >= 11) {
        _map[1][3] = (int)OBJECT::VOID;
        _map[3][1] = (int)OBJECT::VOID;
        _map[3][_x - 2] = (int)OBJECT::VOID;
        _map[1][_x - 4] = (int)OBJECT::VOID;
        _map[_y - 2][_x - 4] = (int)OBJECT::VOID;
        _map[_y - 4][_x - 2] = (int)OBJECT::VOID;
        _map[_y - 2][3] = (int)OBJECT::VOID;
        _map[_y - 4][1] = (int)OBJECT::VOID;
    }
}