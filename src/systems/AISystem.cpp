/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** AISystem
*/

#include "AISystem.hpp"
#include "PathFinderComponent.hpp"
#include "Components.h"

bool Indie::Systems::AISystem::hasMoved(irr::core::vector3df position, irr::core::vector3df nextPosition, Indie::Components::AIComponent *aiComponent) const
{
    // std::cout << "AiX: " << position.X << " aiZ: " << position.Z << std::endl;
    // std::cout << "Next: " << nextPosition.X << " NextY: " << nextPosition.Z << std::endl;

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

int Indie::Systems::AISystem::getCenter(int value) const
{
    if (value % 20 < 10) {
        return value - (value % 20);
    } else {
        return value + 20 - (value % 20);
    }
}

void Indie::Systems::AISystem::onUpdate(irr::f32, EntityManager &entityManager) const
{
    std::vector<std::vector<Indie::Components::OBJECT>> map;
    int aiX = 0;
    int aiZ = 0;

    for (auto entity : entityManager.each<Indie::Components::MapComponent>()) {
        auto mapComponent = entity->getComponent<Indie::Components::MapComponent>();

        map = mapComponent->getMap();

        for (auto entity : entityManager.each<Indie::Components::MoveComponent, Indie::Components::AIComponent, Indie::Components::PositionComponent, Indie::Components::PlayerComponent>()) {

            std::vector<std::vector<Indie::Components::OBJECT>> mapPath;
            std::array<int, 3> position {0, 0, 0};
            auto aiComponent = entity->getComponent<Indie::Components::AIComponent>();
            auto pathFinderComponent = entity->getComponent<Indie::Components::PathFinderComponent>();
            auto moveComponent = entity->getComponent<Indie::Components::MoveComponent>();
            auto positionComponent = entity->getComponent<Indie::Components::PositionComponent>();

            if (pathFinderComponent->getMap().empty())
                pathFinderComponent->setMap(map);
            mapPath = pathFinderComponent->getMap();

            if (aiComponent->getAction() == Indie::Components::ACTION::PLACE_BOMB) {
                moveComponent->setDrop(false);
                aiComponent->setAction(Indie::Components::ACTION::BOMB_PLACED);
            }
            if (aiComponent->getAction() == Indie::Components::ACTION::BOMB_PLACED) {
                moveComponent->setUp(false);
                moveComponent->setDown(false);
                moveComponent->setRight(false);
                moveComponent->setLeft(false);
                return;
            }
            aiX = getCenter(positionComponent->getPosition().X) / 20;
            aiZ = (14 - getCenter(positionComponent->getPosition().Z) / 20);

            if (aiComponent->getDirection() != Indie::Components::DIRECTION::NONE &&
            hasMoved(irr::core::vector3df(positionComponent->getPosition().X, 20, positionComponent->getPosition().Z),irr::core::vector3df((aiComponent->getNextPosition().X) * 20, 20, (14 - aiComponent->getNextPosition().Y) * 20), aiComponent) == false) {
                moveComponent->setUp(isMoving(Indie::Components::DIRECTION::UP, aiComponent));
                moveComponent->setDown(isMoving(Indie::Components::DIRECTION::DOWN, aiComponent));
                moveComponent->setRight(isMoving(Indie::Components::DIRECTION::RIGHT, aiComponent));
                moveComponent->setLeft(isMoving(Indie::Components::DIRECTION::LEFT, aiComponent));
            }
            else {
                if (hasArrived(mapPath, pathFinderComponent) == true && aiComponent->getAction() == Indie::Components::ACTION::STANDBY) {
                    pathFinderComponent->setMap(mapComponent->getMap());
                    pathFinderComponent->setPathFinding(irr::core::vector2di(aiX, aiZ), 4);
                    pathFinderComponent->findPosition(position);
                    pathFinderComponent->getShortlessPath(irr::core::vector2di(aiX, aiZ), irr::core::vector2di(position[0], position[1]));
                    mapPath = pathFinderComponent->getMap();
                }
                else if (hasArrived(mapPath, pathFinderComponent) == true && aiComponent->getAction() == Indie::Components::ACTION::GO_BOX) {
                    aiComponent->setAction(Indie::Components::ACTION::PLACE_BOMB);
                    std::cout << "Bomb posed" << std::endl;
                    moveComponent->setDrop(true);
                }
                else {
                    aiComponent->setNextDirection(mapPath, irr::core::vector2di(aiX, aiZ));
                    aiComponent->setAction(Indie::Components::ACTION::GO_BOX);
                    pathFinderComponent->setMap(mapPath);
                }
            }
        }
    }
}