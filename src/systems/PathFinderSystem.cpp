
/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** PathFinderSystem
*/

#include "PathFinderSystem.hpp"
#include "AIComponent.hpp"
#include "BombComponent.hpp"
#include "MoveComponent.hpp"
#include "PositionComponent.hpp"
#include "PowerUpComponent.hpp"
#include "PowerDownComponent.hpp"
#include "PlayerComponent.hpp"
#include <array>

using namespace Indie::Components;

void Indie::Systems::PathFinderSystem::onUpdate(irr::f32, Indie::EntityManager &entityManager) const
{
    std::vector<std::vector<OBJECT>> map = entityManager.getUniqueEntity<MapComponent>()->getComponent<MapComponent>()->getMap();
    std::vector<std::vector<OBJECT>> mapPathFinding;
    std::vector<std::vector<OBJECT>> mapBomb;
    std::vector<std::vector<OBJECT>> mapPower;
    std::vector<std::vector<OBJECT>> mapEnemy;

    mapPathFinding = map;
    mapBomb = map;
    mapPower = map;
    mapEnemy = map;
    this->setMapBomb(mapBomb, entityManager);
    this->setMapPower(mapPower, entityManager);
    this->cleanMap(map);
    mapEnemy = map;

    for (auto entity : entityManager.each<PathFinderComponent, AIComponent, PositionComponent, MoveComponent>()) {
        auto pathFinder = entity->getComponent<PathFinderComponent>();
        auto ai = entity->getComponent<AIComponent>();
        auto position = entity->getComponent<PositionComponent>();
        auto move = entity->getComponent<MoveComponent>();
        int aiX = (getCenter((int)position->getPosition().X)) / 20;
        int aiZ = (getCenter((int)position->getPosition().Z)) / 20;
        mapEnemy = map;
        this->setMapEnemy(mapEnemy, entityManager, irr::core::vector2di(aiX, aiZ));
        pathFinder->setMapBomb(mapBomb);


        if ((int)mapEnemy.at(aiZ).at(aiX) == 6 && ai->getDodge() == false) {
            ai->setDodge(true);
            ai->setAction(ACTION::DODGE);
            move->setDrop(true);
            pathFinder->setMap(map);
        }
        if ((int)mapEnemy.at(aiZ).at(aiX) != 6 && ai->getDodge() == true) {
            ai->setDodge(false);
            move->setDrop(false);
        }

        if (pathFinder->getMap().empty() || ai->getAction() == ACTION::STANDBY)
            pathFinder->setMap(map);
        mapPathFinding = pathFinder->getMap();
        if (ai->getAction() == ACTION::STANDBY)
            continue;
        setPathFinding(mapPathFinding, {aiX, aiZ}, mapBomb, mapPower);
        if (ai->getAction() == ACTION::DODGE) {
            findFirstPosition(mapPathFinding, mapBomb, mapEnemy, pathFinder, irr::core::vector2di(aiX, aiZ));
            if (pathFinder->getEndMapPos().X == aiX && pathFinder->getEndMapPos().Y == aiZ)
                ai->setAction(ACTION::DODGE);
            setShortlessPath(mapPathFinding, irr::core::vector2di(aiX, aiZ), irr::core::vector2di(pathFinder->getEndMapPos().X, pathFinder->getEndMapPos().Y));
            ai->setAction(ACTION::GO_SAFE);
        }
        else if (ai->getAction() == ACTION::FIND_BOX) {
            if (getNbPowerUpInZone(mapPower, entityManager, irr::core::vector2di(aiX, aiZ)) > 0 && getNbPlayerInZone(map, entityManager, irr::core::vector2di(aiX, aiZ)) == 0)
                findPowerUp(mapPathFinding, mapPower, mapBomb, mapEnemy, pathFinder, irr::core::vector2di(aiX, aiZ));
            else
                findPosition(mapPathFinding, mapBomb, mapEnemy, pathFinder, irr::core::vector2di(aiX, aiZ));
            setShortlessPath(mapPathFinding, irr::core::vector2di(aiX, aiZ), irr::core::vector2di(pathFinder->getEndMapPos().X, pathFinder->getEndMapPos().Y));
            ai->setAction(ACTION::GO_BOX);
        }
        else if ((ai->getAction() == ACTION::GO_BOX || ai->getAction() == ACTION::GO_SAFE) &&
        ai->hasMoved(irr::core::vector3df(irr::f32(position->getPosition().X), 20,
        irr::f32(position->getPosition().Z)),irr::core::vector3df(irr::f32((ai->getNextPosition().X) * 20), 20, irr::f32((ai->getNextPosition().Y) * 20)), ai)) {
            ai->setNextDirection(mapPathFinding, irr::core::vector2di(aiX, aiZ));
            if ((int)mapBomb.at(ai->getNextPosition().Y).at(ai->getNextPosition().X) == 5) {
                ai->setAction(ACTION::STANDBY);
                ai->setDirection(DIRECTION::NONE);
            }
        }
        pathFinder->setMap(mapPathFinding);
    }
}

int Indie::Systems::PathFinderSystem::getNbPlayerInZone(std::vector<std::vector<OBJECT>> map,  EntityManager &entityManager, irr::core::vector2di aiPosition) const
{
    int nbPlayer = 0;

    setPathFinding(map, irr::core::vector2di(aiPosition.X, aiPosition.Y), map, map);
    for (auto entity : entityManager.each<PlayerComponent, PositionComponent>()) {
        auto position = entity->getComponent<PositionComponent>();

        int playerX = (getCenter((int)position->getPosition().X)) / 20;
        int playerZ = (getCenter((int)position->getPosition().Z)) / 20;

        if (map.at(playerZ).at(playerX) >= static_cast<OBJECT>(6) && !(playerX == aiPosition.X && playerZ == aiPosition.Y))
            nbPlayer += 1;
    }
    return nbPlayer;
}

int Indie::Systems::PathFinderSystem::getNbPowerUpInZone(std::vector<std::vector<OBJECT>> map,  EntityManager &entityManager, irr::core::vector2di aiPosition) const
{
    int nbPowerUp = 0;

    setPathFinding(map, irr::core::vector2di(aiPosition.X, aiPosition.Y), map, map);
    for (auto entity : entityManager.each<PowerUpComponent, PositionComponent>()) {
        auto position = entity->getComponent<PositionComponent>();

        int powerX = (getCenter((int)position->getPosition().X)) / 20;
        int powerZ = (getCenter((int)position->getPosition().Z)) / 20;

        if (map.at(powerZ).at(powerX) >= static_cast<OBJECT>(6))
            nbPowerUp += 1;
    }
    return nbPowerUp;
}

int Indie::Systems::PathFinderSystem::getCenter(int value) const
{
    if (value % 20 < 10) {
        return value - (value % 20);
    } else {
        return value + 20 - (value % 20);
    }
}

void Indie::Systems::PathFinderSystem::setPathFinding(std::vector<std::vector<OBJECT>> &map, irr::core::vector2di aiPosition,
std::vector<std::vector<OBJECT>> mapBomb, std::vector<std::vector<OBJECT>> mapPower) const
{
    bool canContinue = true;
    int value = 6;

    cleanMap(map);
    map.at(aiPosition.Y).at(aiPosition.X) = static_cast<OBJECT>(6);
    while (canContinue == true) {
        canContinue = false;
        for (size_t j = 1; j < map.at(0).size(); j++) {
            for (size_t i = 1; i < map.size(); i++) {
                if (map.at(i).at(j) == static_cast<OBJECT>(value) && (mapBomb.at(i).at(j) != static_cast<OBJECT>(5)) && (mapPower.at(i).at(j) != static_cast<OBJECT>(9))) {
                    map.at(i - 1).at(j) = (map.at(i - 1).at(j) == static_cast<OBJECT>(0)) ? static_cast<OBJECT>(value + 1) : map.at(i - 1).at(j);
                    map.at(i + 1).at(j) = (map.at(i + 1).at(j) == static_cast<OBJECT>(0)) ? static_cast<OBJECT>(value + 1) : map.at(i + 1).at(j);
                    map.at(i).at(j + 1) = (map.at(i).at(j + 1) == static_cast<OBJECT>(0)) ? static_cast<OBJECT>(value + 1) : map.at(i).at(j + 1);
                    map.at(i).at(j - 1) = (map.at(i).at(j - 1) == static_cast<OBJECT>(0)) ? static_cast<OBJECT>(value + 1) : map.at(i).at(j - 1);
                    canContinue = true;
                }
            }
        }
        value++;
    }
}

void Indie::Systems::PathFinderSystem::setShortlessPath(std::vector<std::vector<OBJECT>> &map, irr::core::vector2di acPos, irr::core::vector2di nextPos) const
{
    int value = (int)map.at(nextPos.Y).at(nextPos.X);

    if (nextPos.X < 1 || nextPos.Y < 1 || nextPos.X > ((int)map.at(0).size() - 1) || nextPos.Y > ((int)map.size() - 1))
        return;
    if (map.at(acPos.Y).at(acPos.X) != static_cast<OBJECT>(-99)) {
        map.at(nextPos.Y).at(nextPos.X) = static_cast<OBJECT>(-99);
        if (map.at(nextPos.Y + 1).at(nextPos.X) == static_cast<OBJECT>(value - 1))
            setShortlessPath(map, irr::core::vector2di(acPos.X, acPos.Y), irr::core::vector2di(nextPos.X, nextPos.Y + 1));
        else if (map.at(nextPos.Y).at(nextPos.X + 1) == static_cast<OBJECT>(value - 1))
            setShortlessPath(map, irr::core::vector2di(acPos.X, acPos.Y), irr::core::vector2di(nextPos.X + 1, nextPos.Y));
        else if (map.at(nextPos.Y - 1).at(nextPos.X) == static_cast<OBJECT>(value - 1))
            setShortlessPath(map, irr::core::vector2di(acPos.X, acPos.Y), irr::core::vector2di(nextPos.X, nextPos.Y - 1));
        else if (map.at(nextPos.Y).at(nextPos.X - 1) == static_cast<OBJECT>(value - 1))
            setShortlessPath(map, irr::core::vector2di(acPos.X, acPos.Y), irr::core::vector2di(nextPos.X - 1, nextPos.Y));
    }
}

void Indie::Systems::PathFinderSystem::findFirstPosition(std::vector<std::vector<OBJECT>> &map, std::vector<std::vector<OBJECT>> &mapBomb,
std::vector<std::vector<OBJECT>> &mapEnemy, PathFinderComponent *pathFinder, irr::core::vector2di aiPosition) const
{
    int distance = 999;
    int newDistance = 0;

    pathFinder->setEndMapPos(irr::core::vector2di(aiPosition.X, aiPosition.Y));
    for (size_t i = 1; i < map.at(0).size(); i++) {
        for (size_t j = 1; j < map.size(); j++) {
            newDistance = (int)map.at(j).at(i);
            if (mapBomb.at(j).at(i) != static_cast<OBJECT>(6) && map.at(j).at(i) > static_cast<OBJECT>(6) && mapEnemy.at(j).at(i) != static_cast<OBJECT>(6) && newDistance < distance) {
                distance = newDistance;
                pathFinder->setEndMapPos(irr::core::vector2di(irr::s32(i), irr::s32(j)));
            }
        }
    }
}

void Indie::Systems::PathFinderSystem::findPowerUp(std::vector<std::vector<OBJECT>> &map, std::vector<std::vector<OBJECT>> &mapPowerUp,
std::vector<std::vector<OBJECT>> &mapBomb, std::vector<std::vector<OBJECT>> &mapEnemy, PathFinderComponent *pathFinder, irr::core::vector2di aiPosition) const
{
    int distance = 999;
    int newDistance = 0;

    pathFinder->setEndMapPos(irr::core::vector2di(aiPosition.X, aiPosition.Y));
    for (size_t i = 1; i < map.at(0).size(); i++) {
        for (size_t j = 1; j < map.size(); j++) {
            newDistance = (int)map.at(j).at(i);
            if (mapBomb.at(j).at(i) != static_cast<OBJECT>(6) && map.at(j).at(i) > static_cast<OBJECT>(6) &&
            mapPowerUp.at(j).at(i) == static_cast<OBJECT>(10) && mapEnemy.at(j).at(i) != static_cast<OBJECT>(6) && newDistance < distance) {
                distance = newDistance;
                pathFinder->setEndMapPos(irr::core::vector2di(irr::s32(i), irr::s32(j)));
            }
        }
    }
}

void Indie::Systems::PathFinderSystem::findPosition(std::vector<std::vector<OBJECT>> &map, std::vector<std::vector<OBJECT>> &mapBomb,
std::vector<std::vector<OBJECT>> &mapEnemy, PathFinderComponent *pathFinder, irr::core::vector2di aiPosition) const
{
    int aiPosX = aiPosition.X;
    int aiPosY = aiPosition.Y;
    int distance = 999;
    int nbBox = 0;
    int random = 0;

    for (size_t i = 1; i < map.at(0).size(); i++) {
        for (size_t j = 1; j < map.size(); j++) {
            nbBox = 0;
            if (map.at(j).at(i) >= static_cast<OBJECT>(6) && mapEnemy.at(j).at(i) != static_cast<OBJECT>(6) && (mapBomb.at(j).at(i) != static_cast<OBJECT>(6) && mapBomb.at(j).at(i) != static_cast<OBJECT>(5))) {
                nbBox += (map.at(j - 1).at(i) == OBJECT::BOX) ? 1 : 0;
                nbBox += (map.at(j).at(i + 1) == OBJECT::BOX) ? 1 : 0;
                nbBox += (map.at(j + 1).at(i) == OBJECT::BOX) ? 1 : 0;
                nbBox += (map.at(j).at(i - 1) == OBJECT::BOX) ? 1 : 0;
                if (nbBox >= 1 && ((int)map.at(j).at(i)) <= distance) {
                    if (aiPosX != aiPosition.X || aiPosY != aiPosition.Y) {
                        random = std::rand()/((RAND_MAX + 1u) / 10);
                        if (random >= 5) {
                            aiPosX = (int)i;
                            aiPosY = (int)j;
                            distance = (int)map.at(j).at(i);
                        }
                    }
                    else {
                        aiPosX = (int)i;
                        aiPosY = (int)j;
                        distance = (int)map.at(j).at(i);
                    }
                }
            }
        }
    }
    pathFinder->setEndMapPos(irr::core::vector2di(aiPosX, aiPosY));
}

void Indie::Systems::PathFinderSystem::setMapBomb(std::vector<std::vector<OBJECT>> &map,  EntityManager &entityManager) const
{
    for (auto entity : entityManager.each<BombComponent, PositionComponent>()) {
        auto bomb = entity->getComponent<BombComponent>();
        auto position = entity->getComponent<PositionComponent>();
        int x = (getCenter((int)position->getPosition().X)) / 20;
        int z = (getCenter((int)position->getPosition().Z)) / 20;
        unsigned int range = bomb->getRange();
        size_t i = 0;

        map.at(z).at(x) = static_cast<OBJECT>(6);
        for (i = 0; i <= range && z + i < map.size(); i++)
            map.at(z + i).at(x) = (map.at(z + i).at(x) == static_cast<OBJECT>(0)) ? static_cast<OBJECT>(6) : map.at(z + i).at(x);
        for (i = 0; i <= range && x + i < map.at(0).size(); i++)
            map.at(z).at(x + i) = (map.at(z).at(x + i) == static_cast<OBJECT>(0)) ? static_cast<OBJECT>(6) : map.at(z).at(x + i);
        for (i = 0; i <= range && z - i > 0; i++)
            map.at(z - i).at(x) = (map.at(z - i).at(x) == static_cast<OBJECT>(0)) ? static_cast<OBJECT>(6) : map.at(z - i).at(x);
        for (i = 0; i <= range && x - i > 0; i++)
            map.at(z).at(x - i) = (map.at(z).at(x - i) == static_cast<OBJECT>(0)) ? static_cast<OBJECT>(6) : map.at(z).at(x - i);
    }
}

void Indie::Systems::PathFinderSystem::setMapEnemy(std::vector<std::vector<OBJECT>> &map,  EntityManager &entityManager, irr::core::vector2di aiPosition) const
{
    for (auto entity : entityManager.each<PlayerComponent, PositionComponent>()) {
        auto position = entity->getComponent<PositionComponent>();
        int x = (getCenter((int)position->getPosition().X)) / 20;
        int z = (getCenter((int)position->getPosition().Z)) / 20;
        size_t i = 0;

        if (!(x == aiPosition.X && z == aiPosition.Y)) {
            map.at(z).at(x) = static_cast<OBJECT>(6);
            for (i = 0; i <= 2 && z + i < map.size(); i++)
                map.at(z + i).at(x) = (map.at(z + i).at(x) == static_cast<OBJECT>(0)) ? static_cast<OBJECT>(6) : map.at(z + i).at(x);
            for (i = 0; i <= 2 && x + i < map.at(0).size(); i++)
                map.at(z).at(x + i) = (map.at(z).at(x + i) == static_cast<OBJECT>(0)) ? static_cast<OBJECT>(6) : map.at(z).at(x + i);
            for (i = 0; i <= 2 && z - i > 0; i++)
                map.at(z - i).at(x) = (map.at(z - i).at(x) == static_cast<OBJECT>(0)) ? static_cast<OBJECT>(6) : map.at(z - i).at(x);
            for (i = 0; i <= 2 && x - i > 0; i++)
                map.at(z).at(x - i) = (map.at(z).at(x - i) == static_cast<OBJECT>(0)) ? static_cast<OBJECT>(6) : map.at(z).at(x - i);
            map.at(z + 1).at(x + 1) = (map.at(z + 1).at(x + 1) == static_cast<OBJECT>(0)) ? static_cast<OBJECT>(6) : map.at(z + 1).at(x + 1);
            map.at(z - 1).at(x - 1) = (map.at(z - 1).at(x - 1) == static_cast<OBJECT>(0)) ? static_cast<OBJECT>(6) : map.at(z - 1).at(x - 1);
            map.at(z + 1).at(x - 1) = (map.at(z + 1).at(x - 1) == static_cast<OBJECT>(0)) ? static_cast<OBJECT>(6) : map.at(z + 1).at(x - 1);
            map.at(z - 1).at(x + 1) = (map.at(z - 1).at(x + 1) == static_cast<OBJECT>(0)) ? static_cast<OBJECT>(6) : map.at(z - 1).at(x + 1);
        }
    }
}

void Indie::Systems::PathFinderSystem::setMapPower(std::vector<std::vector<OBJECT>> &map,  EntityManager &entityManager) const
{
    for (auto entity : entityManager.each<PowerUpComponent, PositionComponent>()) {
        auto position = entity->getComponent<PositionComponent>();
        int x = (getCenter((int)position->getPosition().X)) / 20;
        int z = (getCenter((int)position->getPosition().Z)) / 20;

        map.at(z).at(x) = static_cast<OBJECT>(10);
    }
    for (auto entity : entityManager.each<PowerDownComponent, PositionComponent>()) {
        auto position = entity->getComponent<PositionComponent>();
        int x = (getCenter((int)position->getPosition().X)) / 20;
        int z = (getCenter((int)position->getPosition().Z)) / 20;

        map.at(z).at(x) = static_cast<OBJECT>(9);
    }
}

void Indie::Systems::PathFinderSystem::cleanMap(std::vector<std::vector<OBJECT>> &map) const
{
    for (size_t j = 1; j < map.at(0).size(); j++) {
        for (size_t i = 1; i < map.size(); i++) {
            if (map.at(i).at(j) > static_cast<OBJECT>(2)) {
                map.at(i).at(j) = static_cast<OBJECT>(0);
            }
        }
    }
}