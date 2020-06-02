
/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** PathFinderSystem
*/

#include "PathFinderSystem.hpp"
#include <iomanip>

using namespace Indie::Components;

void Indie::Systems::PathFinderSystem::onUpdate(irr::f32, Indie::EntityManager &entityManager) const
{
    std::vector<std::vector<OBJECT>> mapPathFinding;
    std::vector<std::vector<OBJECT>> map;
    std::vector<std::vector<OBJECT>> mapBomb;
    std::vector<std::vector<OBJECT>> mapPowerUp;

    for (auto entity : entityManager.each<MapComponent>()) {
        auto mapComponent = entity->getComponent<MapComponent>();

        map = mapComponent->getMap();
        mapBomb = map;
        mapPowerUp = map;
        this->setMapBomb(mapBomb, entityManager);
        this->setMapPowerUp(mapPowerUp, entityManager);
        this->cleanMap(map);
    }

    for (auto entity : entityManager.each<PathFinderComponent, AIComponent, PositionComponent, PlayerComponent>()) {
        auto pathFinder = entity->getComponent<PathFinderComponent>();
        auto ai = entity->getComponent<AIComponent>();
        auto position = entity->getComponent<PositionComponent>();
        auto player = entity->getComponent<PlayerComponent>();
        int aiX = (getCenter((int)position->getPosition().X)) / 20;
        int aiZ = (getCenter((int)position->getPosition().Z)) / 20;

        // Init des maps dans le pathfinder
        pathFinder->setMapBomb(mapBomb);
        if (pathFinder->getMap().empty() || ai->getAction() == ACTION::STANDBY)
            pathFinder->setMap(map);
        mapPathFinding = pathFinder->getMap();

        // Wait d'une update cf AISystem
        if (ai->getAction() == ACTION::WAIT_EXPLOSION)
            ai->setAction(ACTION::STANDBY);
        // S'il fait rien return
        if (ai->getAction() == ACTION::STANDBY)
            return;
        player->setBehavior((unsigned int)getNbPlayerInZone(map, entityManager, irr::core::vector2di(aiX, aiZ)));
        setPathFinding(mapPathFinding, irr::core::vector2di(aiX, aiZ), 6, mapBomb);

        // Get PathFinding quand il doit dodge une bombe qu'il a posé
        if (ai->getAction() == ACTION::DODGE) {
            findFirstPosition(mapPathFinding, mapBomb, pathFinder, irr::core::vector2di(aiX, aiZ));
            if (pathFinder->getEndMapPos().X == -99 || pathFinder->getEndMapPos().Y == -99) {
                ai->setAction(ACTION::DODGE);
                return;
            }
            setShortlessPath(mapPathFinding, irr::core::vector2di(aiX, aiZ), irr::core::vector2di(pathFinder->getEndMapPos().X, pathFinder->getEndMapPos().Y));
            ai->setAction(ACTION::GO_SAFE);
        }
        // Get pathfinding quand cherche une box
        else if (ai->getAction() == ACTION::FIND_BOX) {
            findPosition(mapPathFinding, pathFinder, irr::core::vector2di(aiX, aiZ));
            // Si il est coincé il va pas chercher une box ( pour pas se déplacer et attendre un chemin opti NORMALEMNET MAIS MARCHE PAS)
            if (pathFinder->getEndMapPos().X == -99 || pathFinder->getEndMapPos().Y == -99) {
                ai->setAction(ACTION::WAIT_EXPLOSION);
                return;
            }
            setShortlessPath(mapPathFinding, irr::core::vector2di(aiX, aiZ), irr::core::vector2di(pathFinder->getEndMapPos().X, pathFinder->getEndMapPos().Y));
            ai->setAction(ACTION::GO_BOX);
        }
        // Get Direction pour le movement
        else if ((ai->getAction() == ACTION::GO_BOX || ai->getAction() == ACTION::GO_SAFE || ai->getAction() == ACTION::GO_POWERUP) &&
        ai->hasMoved(irr::core::vector3df(position->getPosition().X, 20, position->getPosition().Z),irr::core::vector3df((ai->getNextPosition().X) * 20, 20, (ai->getNextPosition().Y) * 20), ai)) {
            ai->setNextDirection(mapPathFinding, irr::core::vector2di(aiX, aiZ));
            // Si il est pas coincé il va pas marcher dans la lave ici
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

    setPathFinding(map, irr::core::vector2di(aiPosition.X, aiPosition.Y), 6, map);
    for (auto entity : entityManager.each<PlayerComponent, PositionComponent>()) {
        auto position = entity->getComponent<PositionComponent>();

        int playerX = (getCenter((int)position->getPosition().X)) / 20;
        int playerZ = (getCenter((int)position->getPosition().Z)) / 20;

        if (map.at(playerZ).at(playerX) >= static_cast<OBJECT>(6) && !(playerX == aiPosition.X && playerZ == aiPosition.Y))
            nbPlayer += 1;
    }
    return nbPlayer;
}





















int Indie::Systems::PathFinderSystem::getCenter(int value) const
{
    if (value % 20 < 10) {
        return value - (value % 20);
    } else {
        return value + 20 - (value % 20);
    }
}

bool Indie::Systems::PathFinderSystem::hasArrived(std::vector<std::vector<OBJECT>> &map, PathFinderComponent *pathFinder) const
{
    return map.at(pathFinder->getEndMapPos().Y).at(pathFinder->getEndMapPos().X) != static_cast<OBJECT>(-99);
}

int Indie::Systems::PathFinderSystem::getDistance2D(irr::core::vector2di v1, irr::core::vector2di v2) const
{
    return sqrt((pow(v1.X - v2.X, 2) + pow(v1.Y - v2.Y, 2)));
}















void Indie::Systems::PathFinderSystem::setPathFinding(std::vector<std::vector<OBJECT>> &map, irr::core::vector2di aiPosition, int value, std::vector<std::vector<OBJECT>> mapBomb) const
{
    bool canContinue = true;

    cleanMap(map);
    map.at(aiPosition.Y).at(aiPosition.X) = static_cast<OBJECT>(6);
    while (canContinue == true) {
        canContinue = false;
        for (size_t j = 1; j < map.at(0).size(); j++) {
            for (size_t i = 1; i < map.size(); i++) {
                if (map.at(i).at(j) == static_cast<OBJECT>(value) && mapBomb.at(i).at(j) != static_cast<OBJECT>(5)) {
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
    while (map.at(acPos.Y).at(acPos.X) != static_cast<OBJECT>(-99)) {
        map.at(nextPos.Y).at(nextPos.X) = static_cast<OBJECT>(-99);
        if (map.at(nextPos.Y + 1).at(nextPos.X) == static_cast<OBJECT>(value - 1))
            setShortlessPath(map, irr::core::vector2di(acPos.X, acPos.Y), irr::core::vector2di(nextPos.X, nextPos.Y + 1));
        else if (map.at(nextPos.Y).at(nextPos.X + 1) == static_cast<OBJECT>(value - 1))
            setShortlessPath(map, irr::core::vector2di(acPos.X, acPos.Y), irr::core::vector2di(nextPos.X + 1, nextPos.Y));
        else if (map.at(nextPos.Y - 1).at(nextPos.X) == static_cast<OBJECT>(value - 1))
            setShortlessPath(map, irr::core::vector2di(acPos.X, acPos.Y), irr::core::vector2di(nextPos.X, nextPos.Y - 1));
        else if (map.at(nextPos.Y).at(nextPos.X - 1) == static_cast<OBJECT>(value - 1))
            setShortlessPath(map, irr::core::vector2di(acPos.X, acPos.Y), irr::core::vector2di(nextPos.X - 1, nextPos.Y));
        return;
    }
}





void Indie::Systems::PathFinderSystem::findFirstPosition(std::vector<std::vector<OBJECT>> &map, std::vector<std::vector<OBJECT>> &mapBomb, PathFinderComponent *pathFinder, irr::core::vector2di aiPosition) const
{
    std::array<int, 3> position = {-99, -99, 99};
    int maxValue = 6;


    for (size_t i = 1; i < map.at(0).size(); i++) {
        for (size_t j = 1; j < map.size(); j++) {
            if (map.at(j).at(i) >= static_cast<OBJECT>(maxValue) && (mapBomb.at(j).at(i) == static_cast<OBJECT>(6)) ) {
                if (map.at(j).at(i - 1) > static_cast<OBJECT>(maxValue)) {
                    if (getDistance2D(irr::core::vector2di(aiPosition.X, aiPosition.Y), irr::core::vector2di(i - 1, j)) <= position.at(2)) {
                        maxValue = (int)map.at(j).at(i - 1);
                        position = {(int)i - 1, (int)j, getDistance2D(irr::core::vector2di(aiPosition.X, aiPosition.Y), irr::core::vector2di(i - 1, j))};
                    }
                }
                if (map.at(j).at(i + 1) > static_cast<OBJECT>(maxValue)) {
                    if (getDistance2D(irr::core::vector2di(aiPosition.X, aiPosition.Y), irr::core::vector2di(i + 1, j)) <= position.at(2)) {
                        maxValue = (int)map.at(j).at(i + 1);
                        position = {(int)i + 1, (int)j, getDistance2D(irr::core::vector2di(aiPosition.X, aiPosition.Y), irr::core::vector2di(i + 1, j))};
                    }
                }
                if (map.at(j - 1).at(i) > static_cast<OBJECT>(maxValue)) {
                    if (getDistance2D(irr::core::vector2di(aiPosition.X, aiPosition.Y), irr::core::vector2di(i, j - 1)) <= position.at(2)) {
                        maxValue = (int)map.at(j - 1).at(i);
                        position = {(int)i, (int)j - 1, getDistance2D(irr::core::vector2di(aiPosition.X, aiPosition.Y), irr::core::vector2di(i, j - 1))};
                    }
                }
                if (map.at(j + 1).at(i) > static_cast<OBJECT>(maxValue)) {
                    if (getDistance2D(irr::core::vector2di(aiPosition.X, aiPosition.Y), irr::core::vector2di(i, j + 1)) <= position.at(2)) {
                        maxValue = (int)map.at(j + 1).at(i);
                        position = {(int)i, (int)j + 1, getDistance2D(irr::core::vector2di(aiPosition.X, aiPosition.Y), irr::core::vector2di(i, j + 1))};
                    }
                }
            }
        }
    }
    pathFinder->setEndMapPos(irr::core::vector2di(position.at(0), position.at(1)));
}

void Indie::Systems::PathFinderSystem::findPosition(std::vector<std::vector<OBJECT>> &map, PathFinderComponent *pathFinder, irr::core::vector2di aiPosition) const
{
    std::array<int, 4> position = {-99, -99, -99, 99};
    int nbBox = 0;
    int random = 0;


    for (size_t i = 1; i < map.at(0).size(); i++) {
        for (size_t j = 1; j < map.size(); j++) {
            nbBox = 0;
            if (map.at(j).at(i) >= static_cast<OBJECT>(6)) {
                nbBox += (map.at(j - 1).at(i) == OBJECT::BOX) ? 1 : 0;
                nbBox += (map.at(j).at(i + 1) == OBJECT::BOX) ? 1 : 0;
                nbBox += (map.at(j + 1).at(i) == OBJECT::BOX) ? 1 : 0;
                nbBox += (map.at(j).at(i - 1) == OBJECT::BOX) ? 1 : 0;
                if (nbBox >= 1 && (getDistance2D(irr::core::vector2di(aiPosition.X, aiPosition.Y), irr::core::vector2di(i, j)) <= position.at(3))) {
                    if (position.at(0) != -99) {
                        random = std::rand()/((RAND_MAX + 1u) / 10);
                        if (random >= 5)
                            position = {(int)i, (int)j, nbBox, getDistance2D(irr::core::vector2di(aiPosition.X, aiPosition.Y), irr::core::vector2di(i, j))};
                    }
                    else
                        position = {(int)i, (int)j, nbBox, getDistance2D(irr::core::vector2di(aiPosition.X, aiPosition.Y), irr::core::vector2di(i, j))};
                }
            }
        }
    }
    pathFinder->setEndMapPos(irr::core::vector2di(position.at(0), position.at(1)));
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

void Indie::Systems::PathFinderSystem::setMapPowerUp(std::vector<std::vector<OBJECT>> &map,  EntityManager &entityManager) const
{
    for (auto entity : entityManager.each<PowerUpComponent, PositionComponent>()) {
        auto position = entity->getComponent<PositionComponent>();
        int x = (getCenter((int)position->getPosition().X)) / 20;
        int z = (getCenter((int)position->getPosition().Z)) / 20;

        map.at(z).at(x) = static_cast<OBJECT>(10);
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