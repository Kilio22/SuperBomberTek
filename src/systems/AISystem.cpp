/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** AISystem
*/

#include "AISystem.hpp"
#include "Components.h"

void Indie::Systems::AISystem::onUpdate(irr::f32 deltaTime, EntityManager &entityManager, const ContextManager &) const
{
    std::vector<std::vector<int>> map;
    std::array<int, 3> position;
    int aiX = 0;
    int aiY = 0;

    for (auto entity : entityManager.each<Indie::Components::MoveComponent, Indie::Components::AIComponent, Indie::Components::PositionComponent>()) {
        auto aiComponent = entity->getComponent<Indie::Components::AIComponent>();
        auto moveComponent = entity->getComponent<Indie::Components::MoveComponent>();
        auto positionComponent = entity->getComponent<Indie::Components::PositionComponent>();

        aiX = positionComponent->getPosition().X / 20;
        aiY = positionComponent->getPosition().Y / 20;
        map = aiComponent->getMap();

        if (aiComponent->getDirection() != Indie::Components::AIComponent::NONE && aiComponent->hasMoved(positionComponent->getPosition(), aiComponent->getNextPosition(aiComponent->getNextXDirection(), aiComponent->getNextYDirection())) == false) {
            moveComponent->setUp(aiComponent->isMoving(Indie::Components::AIComponent::UP));
            moveComponent->setDown(aiComponent->isMoving(Indie::Components::AIComponent::DOWN));
            moveComponent->setRight(aiComponent->isMoving(Indie::Components::AIComponent::RIGHT));
            moveComponent->setLeft(aiComponent->isMoving(Indie::Components::AIComponent::LEFT));
        }
        else {
            if (aiComponent->hasArrived(map) == false) {
                aiComponent->setNextDirection(map, aiX, aiY);
            }
            else {
                aiComponent->pathFinder(map, aiX, aiY, 3);
                aiComponent->findPosition(map, aiX, aiY, position);
            }
        }
    }
}