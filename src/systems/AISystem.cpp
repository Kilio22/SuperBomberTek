/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** AISystem
*/

#include "AISystem.hpp"

using namespace Indie::Components;

void Indie::Systems::AISystem::onUpdate(irr::f32, EntityManager &entityManager) const
{
    std::vector<std::vector<OBJECT>> map;
    std::vector<std::vector<OBJECT>> mapPathFinding;

    for (auto entity : entityManager.each<MapComponent>()) {
        auto mapComponent = entity->getComponent<MapComponent>();

        // Get Actuel map
        map = mapComponent->getMap();
    }

    for (auto entity : entityManager.each<MoveComponent, AIComponent, PositionComponent, PathFinderComponent>()) {
        auto ai = entity->getComponent<AIComponent>();
        auto pathFinder = entity->getComponent<PathFinderComponent>();
        auto move = entity->getComponent<MoveComponent>();
        auto position = entity->getComponent<PositionComponent>();

        // SetMap si elle sont vide jamais init
        if (pathFinder->getMap().empty())
            pathFinder->setMap(map);
        if (pathFinder->getMapBomb().empty())
            pathFinder->setMapBomb(map);
        //Get Map Pathfinding
        mapPathFinding = pathFinder->getMap();

        // Bomb placé -> en attente d'instruction
        if (ai->getAction() == ACTION::PLACE_BOMB) {
            move->setDrop(false);
            ai->setAction(ACTION::STANDBY);
        }

        // S'il est sur une bombe et qu'il vient d'en poser une en gros
        if (isOnBomb(pathFinder->getMapBomb(), position) && hasArrived(mapPathFinding, pathFinder) && ai->getAction() == ACTION::STANDBY &&
        ai->hasMoved(irr::core::vector3df(position->getPosition().X, 20, position->getPosition().Z),irr::core::vector3df((irr::f32)((pathFinder->getEndMapPos().X) * 20.f), 20.f, (irr::f32)((pathFinder->getEndMapPos().Y) * 20.f)), ai)) {
            ai->setAction(ACTION::DODGE);
        }
        // Faire le déplacement et check qu'il a bien bougé sur la case.
        if (ai->getDirection() != DIRECTION::NONE &&
        ai->hasMoved(irr::core::vector3df(position->getPosition().X, 20, position->getPosition().Z),irr::core::vector3df((irr::f32)((ai->getNextPosition().X) * 20.f), 20.f, (irr::f32)((ai->getNextPosition().Y) * 20.f)), ai) == false) {
            move->setUp(isMoving(DIRECTION::UP, ai));
            move->setDown(isMoving(DIRECTION::DOWN, ai));
            move->setRight(isMoving(DIRECTION::RIGHT, ai));
            move->setLeft(isMoving(DIRECTION::LEFT, ai));
        }
        // S'il a rien a faire et qu'il a une bombe il va checher une box
        else if (ai->getAction() == ACTION::STANDBY && !hasDropBomb(entityManager, entity->getId())) {
            ai->setAction(ACTION::FIND_BOX);
        }
        // Il pose une bomb s'il est arrivé a coté d'une boite
        else if (hasArrived(mapPathFinding, pathFinder) && ai->getAction() == ACTION::GO_BOX) {
            ai->setAction(ACTION::PLACE_BOMB);
            move->setDrop(true);
            ai->setDirection(DIRECTION::NONE);
        }
        // Mettre en attente s'il est en sécurité
        else if (hasArrived(mapPathFinding, pathFinder) && ai->getAction() == ACTION::GO_SAFE) {
            ai->setAction(ACTION::STANDBY);
            ai->setDirection(DIRECTION::NONE);
        }
    }
}

bool Indie::Systems::AISystem::hasDropBomb(EntityManager &entityManager, int idAi) const
{
    for (auto entity : entityManager.each<BombComponent>()) {
        auto bomb = entity->getComponent<BombComponent>();
        if (bomb->getIdOwner() == idAi)
            return true;
    }
    return false;
}

int Indie::Systems::AISystem::getCenter(int value) const
{
    if (value % 20 < 10) {
        return value - (value % 20);
    } else {
        return value + 20 - (value % 20);
    }
}

bool Indie::Systems::AISystem::isOnBomb(std::vector<std::vector<OBJECT>> map, PositionComponent *position) const
{
    int aiX = (getCenter((int)position->getPosition().X)) / 20;
    int aiZ = (getCenter((int)position->getPosition().Z)) / 20;

    return map.at(aiZ).at(aiX) == static_cast<OBJECT>(6);
}

bool Indie::Systems::AISystem::isMoving(DIRECTION direction, AIComponent *ai) const
{
    return ai->getDirection() == direction;
}

bool Indie::Systems::AISystem::hasArrived(std::vector<std::vector<OBJECT>> &map, PathFinderComponent *pathFinder) const
{
    return map.at(pathFinder->getEndMapPos().Y).at(pathFinder->getEndMapPos().X) != static_cast<OBJECT>(-99);
}