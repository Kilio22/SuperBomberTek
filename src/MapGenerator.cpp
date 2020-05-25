/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** MapGenerator
*/

#include "MapGenerator.hpp"

Indie::MapGenerator::MapGenerator(Indie::EntityBuilder &entityBuilder, irr::core::vector2di vector, Indie::Components::MAP_TYPE type, Indie::Components::THEME theme)
{
    entityBuilder.createMap(vector, type, theme);
}

void Indie::MapGenerator::generate(Indie::EntityManager &entityManager, Indie::EntityBuilder &entityBuilder)
{
    std::string path = "../ressources/static_mesh/";

    for (auto entity : entityManager.each<Indie::Components::MapComponent>()) {
        auto mapComponent = entity->getComponent<Indie::Components::MapComponent>();
        std::vector<std::vector<Components::OBJECT>> map = mapComponent->getMap();

        createWallMap(map, mapComponent->getDimension());
        if (mapComponent->getType() == Indie::Components::MAP_TYPE::RANDOM)
            createRandomMap(map, mapComponent->getDimension());
        else if (mapComponent->getType() == Indie::Components::MAP_TYPE::EMPTY)
            createEmptyMap(map, mapComponent->getDimension());
        else
            createDefaultMap(map, mapComponent->getDimension());
        setSpawn(map, mapComponent->getDimension());
        path += (mapComponent->getTheme() == Indie::Components::THEME::DIRT) ? "map_dirt/" : "map_stone/" ;
        for (int i = mapComponent->getDimension().Y - 1; i >= 0; i--) {
            for (int j = 0; j < mapComponent->getDimension().X; j++) {
                entityBuilder.createGround(irr::core::vector3df((irr::f32)(20 * j), 0, (irr::f32)(20 * i)), path + "ground.obj", path + "ground.png");
                if (map[i][j] == OBJECT::WALL_OUT)
                    entityBuilder.createWall(irr::core::vector3df((irr::f32)(20 * j), 20, (irr::f32)(20 * i)), path + "wall_side.obj", path + "wall_side.png", false);
                else if (map[i][j] == OBJECT::BOX)
                    entityBuilder.createWall(irr::core::vector3df((irr::f32)(20 * j), 20, (irr::f32)(20 * i)), path + "box.obj", path + "box.png", false);
                else if (map[i][j] == OBJECT::WALL_IN)
                    entityBuilder.createWall(irr::core::vector3df((irr::f32)(20 * j), 20, (irr::f32)(20 * i)), path + "wall_middle.obj", path + "wall_middle.png", false);
            }
        }
        mapComponent->setMap(map);
    }
}

void Indie::MapGenerator::createWallMap(std::vector<std::vector<Indie::Components::OBJECT>> &map, irr::core::vector2di dimension)
{
    for (int i = dimension.Y - 1; i >= 0; i--) {
        for (int j = 0; j < dimension.X; j++) {
            if (i == 0 || j == 0 || i == dimension.Y - 1 || j == dimension.X - 1)
                map[i][j] = OBJECT::WALL_OUT;
        }
    }
}

void Indie::MapGenerator::createDefaultMap(std::vector<std::vector<Indie::Components::OBJECT>> &map, irr::core::vector2di dimension)
{
    for (int i = 1; i < dimension.Y - 1; i++) {
        for (int j = 1; j < dimension.X - 1; j++) {
            if (dimension.X % 2 == 1 || dimension.Y % 2 == 1)
                map[i][j] = (j % 2 == 0 && i % 2 == 0) ? OBJECT::WALL_IN : OBJECT::BOX;
            else
                map[i][j] = (j % 2 == 0 && i % 2 == 0 && i < dimension.X - 2 && j < dimension.Y - 2) ? OBJECT::WALL_IN : OBJECT::BOX ;
        }
    }
}

void Indie::MapGenerator::createRandomMap(std::vector<std::vector<Indie::Components::OBJECT>> &map, irr::core::vector2di dimension)
{
    std::srand((unsigned int)std::time(nullptr));
    int random = 0;

    for (int i = 1; i < dimension.Y - 1; i++) {
        for (int j = 1; j < dimension.X - 1; j++) {
            random = 1 + std::rand()/((RAND_MAX + 1u) / 100);
            if (random <= 50)
                map[i][j] = OBJECT::WALL_IN;
            else {
                random = 1 + std::rand()/((RAND_MAX + 1u) / 100);
                map[i][j] = (random <= 40) ? OBJECT::BOX : OBJECT::VOID;
            }
        }
    }
}

void Indie::MapGenerator::createEmptyMap(std::vector<std::vector<Indie::Components::OBJECT>> &map, irr::core::vector2di dimension)
{
    for (int i = 1; i < dimension.Y - 1; i++) {
        for (int j = 1; j < dimension.X - 1; j++) {
            map[i][j] = OBJECT::VOID;
        }
    }
}

void Indie::MapGenerator::setSpawn(std::vector<std::vector<Indie::Components::OBJECT>> &map, irr::core::vector2di dimension)
{
    map[1][1] = OBJECT::VOID;
    map[1][2] = OBJECT::VOID;
    map[2][1] = OBJECT::VOID;
    map[1][dimension.X - 2] = OBJECT::VOID;
    map[1][dimension.X - 3] = OBJECT::VOID;
    map[2][dimension.X - 2] = OBJECT::VOID;
    map[dimension.Y - 2][dimension.X - 2] = OBJECT::VOID;
    map[dimension.Y - 2][dimension.X - 3] = OBJECT::VOID;
    map[dimension.Y - 3][dimension.X - 2] = OBJECT::VOID;
    map[dimension.Y - 2][1] = OBJECT::VOID;
    map[dimension.Y - 2][2] = OBJECT::VOID;
    map[dimension.Y - 3][1] = OBJECT::VOID;
    if (dimension.X >= 11  && dimension.Y >= 11) {
        map[1][3] = OBJECT::VOID;
        map[3][1] = OBJECT::VOID;
        map[3][dimension.X - 2] = OBJECT::VOID;
        map[1][dimension.X - 4] = OBJECT::VOID;
        map[dimension.Y - 2][dimension.X - 4] = OBJECT::VOID;
        map[dimension.Y - 4][dimension.X - 2] = OBJECT::VOID;
        map[dimension.Y - 2][3] = OBJECT::VOID;
        map[dimension.Y - 4][1] = OBJECT::VOID;
    }
}