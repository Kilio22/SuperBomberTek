/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** MapSystem
*/

#include "MapSystem.hpp"
#include "Components.h"
#include "EntityBuilder.hpp"

void Indie::Systems::MapSystem::onUpdate(irr::f32 deltaTime, EntityManager &entityManager) const
{}

void Indie::Systems::MapSystem::render(EntityManager &entityManager)
{
    auto &entityBuilder = ServiceLocator::getInstance().get<EntityBuilder>();
    std::string path = "../ressources/static_mesh/";

    for (auto entity : entityManager.each<Indie::Components::MapComponent>()) {
        auto mapComponent = entity->getComponent<Indie::Components::MapComponent>();
        std::vector<std::vector<int>> map = mapComponent->getMap();

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
                if (map[i][j] == -1)
                    entityBuilder.createWall(irr::core::vector3df((irr::f32)(20 * j), 20, (irr::f32)(20 * i)), path + "wall_side.obj", path + "wall_side.png", false);
                else if (map[i][j] == 1)
                    entityBuilder.createWall(irr::core::vector3df((irr::f32)(20 * j), 20, (irr::f32)(20 * i)), path + "box.obj", path + "box.png", false);
                else if (map[i][j] == 2)
                    entityBuilder.createWall(irr::core::vector3df((irr::f32)(20 * j), 20, (irr::f32)(20 * i)), path + "wall_middle.obj", path + "wall_middle.png", false);
            }
        }
    }
}

void Indie::Systems::MapSystem::createWallMap(std::vector<std::vector<int>> &map, irr::core::vector2di dimension)
{
    for (int i = dimension.Y - 1; i >= 0; i--) {
        for (int j = 0; j < dimension.X; j++) {
            if (i == 0 || j == 0 || i == dimension.Y - 1 || j == dimension.X - 1)
                map[i][j] = -1;
        }
    }
}

void Indie::Systems::MapSystem::createDefaultMap(std::vector<std::vector<int>> &map, irr::core::vector2di dimension)
{
    for (int i = 1; i < dimension.Y - 1; i++) {
        for (int j = 1; j < dimension.X - 1; j++) {
            if (dimension.X % 2 == 1 || dimension.Y % 2 == 1)
                map[i][j] = (j % 2 == 0 && i % 2 == 0) ? 2 : 1;
            else
                map[i][j] = (j % 2 == 0 && i % 2 == 0 && i < dimension.X - 2 && j < dimension.Y - 2) ? 2 : 1;
        }
    }
}

void Indie::Systems::MapSystem::createRandomMap(std::vector<std::vector<int>> &map, irr::core::vector2di dimension)
{
    std::srand((unsigned int)std::time(nullptr));
    int random = 0;
    
    for (int i = 1; i < dimension.Y - 1; i++) {
        for (int j = 1; j < dimension.X - 1; j++) {
            random = 1 + std::rand()/((RAND_MAX + 1u) / 100);
            if (random <= 50)
                map[i][j] = 1;
            else {
                random = 1 + std::rand()/((RAND_MAX + 1u) / 100);
                map[i][j] = (random <= 40) ? 2 : 0;
            }
        }
    }
}

void Indie::Systems::MapSystem::createEmptyMap(std::vector<std::vector<int>> &map, irr::core::vector2di dimension)
{
    for (int i = 1; i < dimension.Y - 1; i++) {
        for (int j = 1; j < dimension.X - 1; j++) {
            map[i][j] = -1;
        }
    }
}

void Indie::Systems::MapSystem::setSpawn(std::vector<std::vector<int>> &map, irr::core::vector2di dimension)
{
    map[1][1] = 0;
    map[1][2] = 0;
    map[2][1] = 0;
    map[1][dimension.X - 2] = 0;
    map[1][dimension.X - 3] = 0;
    map[2][dimension.X - 2] = 0;
    map[dimension.Y - 2][dimension.X - 2] = 0;
    map[dimension.Y - 2][dimension.X - 3] = 0;
    map[dimension.Y - 3][dimension.X - 2] = 0;
    map[dimension.Y - 2][1] = 0;
    map[dimension.Y - 2][2] = 0;
    map[dimension.Y - 3][1] = 0;
    if (dimension.X >= 11  && dimension.Y >= 11) {
        map[1][3] = 0;
        map[3][1] = 0;
        map[3][dimension.X - 2] = 0;
        map[1][dimension.X - 4] = 0;
        map[dimension.Y - 2][dimension.X - 4] = 0;
        map[dimension.Y - 4][dimension.X - 2] = 0;
        map[dimension.Y - 2][3] = 0;
        map[dimension.Y - 4][1] = 0;
    }
}