/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** AISystem
*/

#include "AISystem.hpp"
#include "Components.h"

void Indie::Systems::AISystem::onUpdate(irr::f32, EntityManager &entityManager) const
{
    std::vector<std::vector<Indie::Components::OBJECT>> map;
    std::array<int, 3> position {0, 0, 0};
    int aiX = 0;
    int aiY = 0;

    for (auto entity : entityManager.each<Indie::Components::MapComponent>()) {
        auto mapComponent = entity->getComponent<Indie::Components::MapComponent>();

        map = mapComponent->getMap();
        for (auto entity : entityManager.each<Indie::Components::MoveComponent, Indie::Components::AIComponent, Indie::Components::PositionComponent>()) {
            auto aiComponent = entity->getComponent<Indie::Components::AIComponent>();
            auto moveComponent = entity->getComponent<Indie::Components::MoveComponent>();
            auto positionComponent = entity->getComponent<Indie::Components::PositionComponent>();

            aiX = positionComponent->getPosition().X / 20;
            aiY = positionComponent->getPosition().Y / 20;

            if (aiX == aiComponent->getNextXDirection() && aiY == aiComponent->getNextYDirection()) {
                aiComponent->setDirection(Indie::Components::DIRECTION::NONE);
                return;
            }

            if (aiComponent->getDirection() != Indie::Components::DIRECTION::NONE && aiComponent->hasMoved(irr::core::vector3df(aiX * 20, 20, aiY * 20), irr::core::vector3df(aiComponent->getNextXDirection() * 20, 20, aiComponent->getNextYDirection() * 20)) == false) {
                moveComponent->setUp(aiComponent->isMoving(Indie::Components::DIRECTION::UP));
                moveComponent->setDown(aiComponent->isMoving(Indie::Components::DIRECTION::DOWN));
                moveComponent->setRight(aiComponent->isMoving(Indie::Components::DIRECTION::RIGHT));
                moveComponent->setLeft(aiComponent->isMoving(Indie::Components::DIRECTION::LEFT));
            }
            else {
                if (aiComponent->hasArrived(map) == false) {
                    aiComponent->setPathFinding(map, irr::core::vector2di(aiX, aiY), 4);
                    aiComponent->findPosition(map, position);
                    aiComponent->getShortlessPath(map, irr::core::vector2di(aiX, aiY), irr::core::vector2di(position[0], position[1]));
                }
                else {
                    aiComponent->setNextDirection(map, aiX, aiY);
                }
            }

        }
        mapComponent->setMap(map);
    }
}