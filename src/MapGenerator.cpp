/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** MapGenerator
*/

#include "MapGenerator.hpp"
#include "FileCorruptedException.hpp"
#include "FileNotFoundException.hpp"
#include <fstream>
#include <sstream>
#include <iterator>

using namespace Indie::Components;

Indie::MapGenerator::MapGenerator(Indie::EntityBuilder &entityBuilder, irr::core::vector2di vector, Indie::Components::MAP_TYPE type,
    Indie::Components::THEME theme, const std::string &mapPath)
{
    entityBuilder.createMap(vector, type, theme, mapPath);
}

void Indie::MapGenerator::generate(Indie::EntityManager &entityManager, Indie::EntityBuilder &entityBuilder)
{
    std::string path = "../ressources/static_mesh/";
    auto mapComponent = entityManager.getUniqueEntity<MapComponent>()->getComponent<MapComponent>();
    std::vector<std::vector<Components::OBJECT>> map = mapComponent->getMap();

    createWallMap(map, mapComponent->getDimension());
    if (mapComponent->getType() == Indie::Components::MAP_TYPE::RANDOM)
        createRandomMap(map, mapComponent->getDimension());
    else if (mapComponent->getType() == Indie::Components::MAP_TYPE::EMPTY)
        createEmptyMap(map, mapComponent->getDimension());
    else {
        if (mapComponent->getType() == Indie::Components::MAP_TYPE::SAVED)
            this->createSavedMap(map, mapComponent->getMapPath(), mapComponent->getDimension());
        else
            createDefaultMap(map, mapComponent->getDimension());
    }
    if (mapComponent->getType() != Indie::Components::MAP_TYPE::SAVED) {
        setSpawn(map, mapComponent->getDimension());
    }
    path += (mapComponent->getTheme() == Indie::Components::THEME::DIRT) ? "map_dirt/" : "map_stone/";
    for (int i = mapComponent->getDimension().Y - 1; i >= 0; i--) {
        for (int j = 0; j < mapComponent->getDimension().X; j++) {
            entityBuilder.createGround({ (irr::f32)(20 * j), 0, (irr::f32)(20 * i) }, path + "ground.obj", path + "ground.png");
            if (map.at(i).at(j) == OBJECT::WALL_OUT)
                entityBuilder.createWall({ (irr::f32)(20 * j), 20, (irr::f32)(20 * i) }, path + "wall_side.obj", path + "wall_side.png", false);
            else if (map.at(i).at(j) == OBJECT::BOX)
                entityBuilder.createWall({ (irr::f32)(20 * j), 20, (irr::f32)(20 * i) }, path + "box.obj", path + "box.png", true);
            else if (map.at(i).at(j) == OBJECT::WALL_IN)
                entityBuilder.createWall({ (irr::f32)(20 * j), 20, (irr::f32)(20 * i) }, path + "wall_middle.obj", path + "wall_middle.png", false);
        }
    }
    mapComponent->setMap(map);
}

void Indie::MapGenerator::createWallMap(std::vector<std::vector<Indie::Components::OBJECT>> &map, irr::core::vector2di dimension)
{
    for (int i = dimension.Y - 1; i >= 0; i--) {
        for (int j = 0; j < dimension.X; j++) {
            if (i == 0 || j == 0 || i == dimension.Y - 1 || j == dimension.X - 1)
                map.at(i).at(j) = OBJECT::WALL_OUT;
        }
    }
}

void Indie::MapGenerator::createDefaultMap(std::vector<std::vector<Indie::Components::OBJECT>> &map, irr::core::vector2di dimension)
{
    for (int i = 1; i < dimension.Y - 1; i++) {
        for (int j = 1; j < dimension.X - 1; j++) {
            if (dimension.X % 2 == 1 || dimension.Y % 2 == 1)
                map.at(i).at(j) = (j % 2 == 0 && i % 2 == 0) ? OBJECT::WALL_IN : OBJECT::BOX;
            else
                map.at(i).at(j) = (j % 2 == 0 && i % 2 == 0 && i < dimension.X - 2 && j < dimension.Y - 2) ? OBJECT::WALL_IN : OBJECT::BOX;
        }
    }
}

void Indie::MapGenerator::createRandomMap(std::vector<std::vector<Indie::Components::OBJECT>> &map, irr::core::vector2di dimension)
{
    int placedBlocks = 0;

    for (int i = 2; i < dimension.Y - 1; i++) {
        for (int j = 1; j < dimension.X - 1; j++) {
            if (j % 2 == 0 && i % 2 == 0)
                map.at(i).at(j) = OBJECT::WALL_IN;
        }
    }
    for (int j = 2, maxBlockNbUp = 5, maxBlockNbDown = 5; j < dimension.X - 3; j++) {
        if (std::rand() % 40 > 10 && maxBlockNbUp > 0) {
            maxBlockNbUp--;
            map.at(dimension.Y - 2).at(j) = OBJECT::BOX;
            placedBlocks++;
        }
        if (std::rand() % 40 > 10 && maxBlockNbDown > 0) {
            maxBlockNbDown--;
            placedBlocks++;
            map.at(1).at(j) = OBJECT::BOX;
        }
    }
    for (int i = 2, maxBlockNbLeft = 5, maxBlockNbRight = 5; i < dimension.Y - 2; i++) {
        if (std::rand() % 40 > 10 && maxBlockNbLeft > 0) {
            maxBlockNbLeft--;
            placedBlocks++;
            map.at(i).at(1) = OBJECT::BOX;
        }
        if (std::rand() % 40 > 10 && maxBlockNbRight > 0) {
            maxBlockNbRight--;
            placedBlocks++;
            map.at(i).at(dimension.X - 2) = OBJECT::BOX;
        }
    }
    double fillPercentage = (double)(std::rand() % 25 + 25);
    int maxBlockNb = (dimension.Y - 2) * (dimension.X - 2) - placedBlocks;
    double currentPercentage = 0;

    placedBlocks = 0;
    while (currentPercentage < fillPercentage) {
        int i = rand() % (dimension.Y - 3) + 1;
        int j = rand() % (dimension.X - 3) + 1;

        if (map.at(i).at(j) != OBJECT::WALL_IN) {
            map.at(i).at(j) = OBJECT::BOX;
            placedBlocks++;
        }
        currentPercentage = (((double)placedBlocks / (double)maxBlockNb) * 100.0);
    }
}

void Indie::MapGenerator::createEmptyMap(std::vector<std::vector<Indie::Components::OBJECT>> &map, irr::core::vector2di dimension)
{
    for (int i = 1; i < dimension.Y - 1; i++) {
        for (int j = 1; j < dimension.X - 1; j++) {
            map.at(i).at(j) = OBJECT::VOID;
        }
    }
}

void Indie::MapGenerator::createSavedMap(
    std::vector<std::vector<Components::OBJECT>> &map, const std::string &mapPath, irr::core::vector2di dimension)
{
    std::ifstream ifs(mapPath);
    std::string line;
    std::vector<int> data;
    std::vector<Components::OBJECT> transformedData;

    if (ifs.is_open() == false) {
        throw Indie::Exceptions::FileNotFoundException(ERROR_STR, "File " + mapPath + " not found.");
    }
    map.clear();
    while (std::getline(ifs, line)) {
        std::istringstream iss(line);

        std::copy(std::istream_iterator<int>(iss), std::istream_iterator<int>(), std::back_inserter(data));
        std::transform(data.begin(), data.end(), std::back_inserter(transformedData), [](int n) { return static_cast<Components::OBJECT>(n); });
        map.push_back(transformedData);
        if ((int)transformedData.size() != dimension.X) {
            throw Indie::Exceptions::FileCorruptedException(ERROR_STR, "File " + mapPath + " currupted.");
        }
        data.clear();
        transformedData.clear();
    }
    if ((int)map.size() != dimension.Y) {
        throw Indie::Exceptions::FileCorruptedException(ERROR_STR, "File " + mapPath + " corrupted.");
    }
}

void Indie::MapGenerator::setSpawn(std::vector<std::vector<Indie::Components::OBJECT>> &map, irr::core::vector2di dimension)
{
    map.at(1).at(1) = OBJECT::VOID;
    map.at(1).at(2) = OBJECT::VOID;
    map.at(2).at(1) = OBJECT::VOID;
    map.at(1).at(dimension.X - 2) = OBJECT::VOID;
    map.at(1).at(dimension.X - 3) = OBJECT::VOID;
    map.at(2).at(dimension.X - 2) = OBJECT::VOID;
    map.at(dimension.Y - 2).at(dimension.X - 2) = OBJECT::VOID;
    map.at(dimension.Y - 2).at(dimension.X - 3) = OBJECT::VOID;
    map.at(dimension.Y - 3).at(dimension.X - 2) = OBJECT::VOID;
    map.at(dimension.Y - 2).at(1) = OBJECT::VOID;
    map.at(dimension.Y - 2).at(2) = OBJECT::VOID;
    map.at(dimension.Y - 3).at(1) = OBJECT::VOID;
    if (dimension.X >= 11 && dimension.Y >= 11) {
        map.at(1).at(3) = OBJECT::BOX;
        map.at(3).at(1) = OBJECT::BOX;
        map.at(3).at(dimension.X - 2) = OBJECT::BOX;
        map.at(1).at(dimension.X - 4) = OBJECT::BOX;
        map.at(dimension.Y - 2).at(dimension.X - 4) = OBJECT::BOX;
        map.at(dimension.Y - 4).at(dimension.X - 2) = OBJECT::BOX;
        map.at(dimension.Y - 4).at(1) = OBJECT::BOX;
        map.at(dimension.Y - 2).at(3) = OBJECT::BOX;
    }
}