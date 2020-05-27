/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** AISystem
*/

#include "AISystem.hpp"
#include "PathFinderComponent.hpp"
#include "MoveComponent.hpp"
#include "Components.h"

void Indie::Systems::AISystem::onUpdate(irr::f32, EntityManager &entityManager) const
{
    std::vector<std::vector<Indie::Components::OBJECT>> map;
    std::vector<std::vector<Indie::Components::OBJECT>> mapBomb;
    int aiX = 0;
    int aiZ = 0;

    for (auto entity : entityManager.each<Indie::Components::MapComponent>()) {
        auto mapComponent = entity->getComponent<Indie::Components::MapComponent>();

        map = mapComponent->getMap();
        mapBomb = map;
        determineBomb(mapBomb, entityManager);
    }

    for (auto entity : entityManager.each<Indie::Components::MoveComponent, Indie::Components::AIComponent, Indie::Components::PositionComponent, Indie::Components::PathFinderComponent, Indie::Components::PlayerComponent>()) {
        std::vector<std::vector<Indie::Components::OBJECT>> mapPath;
        std::array<int, 3> position {0, 0, 0};
        auto aiComponent = entity->getComponent<Indie::Components::AIComponent>();
        auto pathFinderComponent = entity->getComponent<Indie::Components::PathFinderComponent>();
        auto moveComponent = entity->getComponent<Indie::Components::MoveComponent>();
        auto positionComponent = entity->getComponent<Indie::Components::PositionComponent>();
        auto playerComponent = entity->getComponent<Indie::Components::PlayerComponent>();

        if (pathFinderComponent->getMap().empty())
            pathFinderComponent->setMap(map);
        mapPath = pathFinderComponent->getMap();

        if (playerComponent->getCurrentBombNb() == 0 && aiComponent->getAction() == Indie::Components::ACTION::HAS_DODGE) {
            return;
        }

        if (aiComponent->getAction() == Indie::Components::ACTION::HAS_DODGE && playerComponent->getCurrentBombNb() == 1)
            aiComponent->setAction(Indie::Components::ACTION::CAN_MOVE);

        if (aiComponent->getAction() == Indie::Components::ACTION::CAN_MOVE) {
            pathFinderComponent->cleanMap();
            aiComponent->setAction(Indie::Components::ACTION::STANDBY);
        }
        if (aiComponent->getAction() == Indie::Components::ACTION::PLACE_BOMB) {
            moveComponent->setDrop(false);
            pathFinderComponent->setMap(map);
            aiComponent->setAction(Indie::Components::ACTION::STANDBY);
        }

        aiX = getCenter((int)positionComponent->getPosition().X) / 20;
        aiZ = (14 - getCenter((int)positionComponent->getPosition().Z) / 20);

        if (aiComponent->getDirection() != Indie::Components::DIRECTION::NONE &&
        hasMoved(irr::core::vector3df(positionComponent->getPosition().X, 20, positionComponent->getPosition().Z),irr::core::vector3df((aiComponent->getNextPosition().X) * 20, 20, (14 - aiComponent->getNextPosition().Y) * 20), aiComponent) == false) {
            moveComponent->setUp(isMoving(Indie::Components::DIRECTION::UP, aiComponent));
            moveComponent->setDown(isMoving(Indie::Components::DIRECTION::DOWN, aiComponent));
            moveComponent->setRight(isMoving(Indie::Components::DIRECTION::RIGHT, aiComponent));
            moveComponent->setLeft(isMoving(Indie::Components::DIRECTION::LEFT, aiComponent));
        }
        else {
            if (isOnBomb(mapBomb, positionComponent) && aiComponent->getAction() == Indie::Components::ACTION::STANDBY) {
                pathFinderComponent->setPathFindingBombDodge(irr::core::vector2di(aiX, aiZ), 6, mapBomb);
                pathFinderComponent->findFirstPosition(position);
                pathFinderComponent->getShortlessPath(irr::core::vector2di(aiX, aiZ), irr::core::vector2di(position[0], position[1]));
                mapPath = pathFinderComponent->getMap();
                aiComponent->setAction(Indie::Components::ACTION::DODGE);
            }
            else if (hasArrived(mapPath, pathFinderComponent) == true && aiComponent->getAction() == Indie::Components::ACTION::DODGE) {
                pathFinderComponent->setMap(map);
                aiComponent->setAction(Indie::Components::ACTION::HAS_DODGE);
            }
            else if (hasArrived(mapPath, pathFinderComponent) == true && aiComponent->getAction() == Indie::Components::ACTION::STANDBY) {
                pathFinderComponent->setMap(map);
                pathFinderComponent->setPathFinding(irr::core::vector2di(aiX, aiZ), 6, mapBomb);
                pathFinderComponent->findPosition(position);
                pathFinderComponent->getShortlessPath(irr::core::vector2di(aiX, aiZ), irr::core::vector2di(position[0], position[1]));
                mapPath = pathFinderComponent->getMap();
                aiComponent->setAction(Indie::Components::ACTION::GO_BOX);

            }
            else if (hasArrived(mapPath, pathFinderComponent) == true && aiComponent->getAction() == Indie::Components::ACTION::GO_BOX) {
                aiComponent->setAction(Indie::Components::ACTION::PLACE_BOMB);
                moveComponent->setDrop(true);
            }
            else {
                aiComponent->setNextDirection(mapPath, irr::core::vector2di(aiX, aiZ));
                pathFinderComponent->setMap(mapPath);
            }
        }
    }
}

bool Indie::Systems::AISystem::isOnBomb(std::vector<std::vector<Indie::Components::OBJECT>> &map, Indie::Components::PositionComponent *positionComponent) const
{
    int aiX = getCenter(positionComponent->getPosition().X) / 20;
    int aiZ = (14 - getCenter(positionComponent->getPosition().Z) / 20);
    return (map[aiZ][aiX] == static_cast<Indie::Components::OBJECT>(5));
}

bool Indie::Systems::AISystem::hasMoved(irr::core::vector3df position, irr::core::vector3df nextPosition, Indie::Components::AIComponent *aiComponent) const
{
    if (aiComponent->getDirection() == Indie::Components::DIRECTION::UP && position.Z < nextPosition.Z)
        return false;
    if (aiComponent->getDirection() == Indie::Components::DIRECTION::DOWN && position.Z > nextPosition.Z)
        return false;
    if (aiComponent->getDirection() == Indie::Components::DIRECTION::RIGHT && position.X < nextPosition.X)
        return false;
    if (aiComponent->getDirection() == Indie::Components::DIRECTION::LEFT && position.X > nextPosition.X)
        return false;
    return true;
}

bool Indie::Systems::AISystem::isMoving(Indie::Components::DIRECTION direction, Indie::Components::AIComponent *aiComponent) const
{
    return (aiComponent->getDirection() == direction);
}

bool Indie::Systems::AISystem::hasArrived(std::vector<std::vector<Indie::Components::OBJECT>> &map, Indie::Components::PathFinderComponent *pathFinderComponent) const
{
    return map[pathFinderComponent->getEndPosition().Y][pathFinderComponent->getEndPosition().X] != static_cast<Indie::Components::OBJECT>(-99) ? true : false;
}

void Indie::Systems::AISystem::determineBomb(std::vector<std::vector<Indie::Components::OBJECT>> &map,  EntityManager &entityManager) const
{
    for (auto entity : entityManager.each<Indie::Components::BombComponent, Indie::Components::PositionComponent>()) {
        auto bomb = entity->getComponent<Indie::Components::BombComponent>();
        auto position = entity->getComponent<Indie::Components::PositionComponent>();
        int x = (int)(position->getPosition().X / 20);
        int z = (int)(14 - position->getPosition().Z / 20);
        unsigned int range = bomb->getRange();
        int i = 0;

        map[z][x] = static_cast<Indie::Components::OBJECT>(5);
        for (i = 0; i <= range && z + i < 15; i++)
            map[z + i][x] = (map[z + i][x] == static_cast<Indie::Components::OBJECT>(0)) ? static_cast<Indie::Components::OBJECT>(5) : map[z + i][x];
        for (i = 0; i <= range && x + i < 15; i++)
            map[z][x + i] = (map[z][x + i] == static_cast<Indie::Components::OBJECT>(0)) ? static_cast<Indie::Components::OBJECT>(5) : map[z][x + i];
        for (i = 0; i <= range && z - i > 0; i++)
            map[z - i][x] = (map[z - i][x] == static_cast<Indie::Components::OBJECT>(0)) ? static_cast<Indie::Components::OBJECT>(5) : map[z - i][x];
        for (i = 0; i <= range && x - i > 0; i++)
            map[z][x - i] = (map[z][x - i] == static_cast<Indie::Components::OBJECT>(0)) ? static_cast<Indie::Components::OBJECT>(5) : map[z][x - i];
    }
}

int Indie::Systems::AISystem::getCenter(int value) const
{
    if (value % 20 < 10) {
        return value - (value % 20);
    } else {
        return value + 20 - (value % 20);
    }
}





























































    // for (int i = 15 - 1; i >= 0; i--) {
    //     for (int j = 0; j < 15; j++) {
    //         std::cout << map[i][j] << " ";
    //     }
    //     std::cout << std::endl;
    // }