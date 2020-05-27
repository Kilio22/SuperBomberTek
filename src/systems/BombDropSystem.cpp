/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** BombDropSystem
*/

#include "BombDropSystem.hpp"
#include "Components.h"
#include "EntityBuilder.hpp"
#include <iostream>

std::vector<std::vector<Indie::Components::OBJECT>> Indie::Systems::BombDropSystem::updateMap(
    std::vector<std::vector<Components::OBJECT>> currentMap, irr::f32 midX, irr::f32 midZ) const
{
    currentMap[(int)(midX / 20)][(int)(midZ / 20)] = OBJECT::BOMB;
    for (auto oui : currentMap) {
        for (auto non : oui) {
            std::cout << (int)non;
        }
        std::cout << std::endl;
    }
    return currentMap;
}

bool Indie::Systems::BombDropSystem::hasBombAtPosition(EntityManager &entityManager, irr::core::vector3df position) const
{
    for (auto bomb : entityManager.each<Components::PositionComponent, Components::BombComponent>()) {
        auto positionComponent = bomb->getComponent<Components::PositionComponent>();
        if (positionComponent->getPosition() == position)
            return true;
    }
    return false;
}

int Indie::Systems::BombDropSystem::getCenter(int value) const
{
    if (value % 20 < 10) {
        return value - (value % 20);
    } else {
        return value + 20 - (value % 20);
    }
}

bool Indie::Systems::BombDropSystem::checkBombPositionWallPass(EntityManager &entityManager, int midX, int midZ) const
{
    for (auto map : entityManager.each<MapComponent>()) {
        auto mapComponent = map->getComponent<MapComponent>();
        auto array = mapComponent->getMap();

        for (size_t i = 0; i < mapComponent->getDimension().Y; i++) {
            for (size_t j = 0; j < mapComponent->getDimension().X; j++) {
                if (array[i][j] == OBJECT::VOID && j * 20 == midX && i * 20 == midZ) {
                    return true;
                }
            }
        }
    }
    return false;
}

void Indie::Systems::BombDropSystem::onUpdate(irr::f32, EntityManager &entityManager) const
{
    auto &entityBuilder = ServiceLocator::getInstance().get<EntityBuilder>();

    for (auto entity : entityManager.each<Components::MoveComponent, Components::PositionComponent, Components::PlayerComponent>()) {
        auto moveComponent = entity->getComponent<Components::MoveComponent>();
        auto positionComponent = entity->getComponent<Components::PositionComponent>();
        auto playerComponent = entity->getComponent<Components::PlayerComponent>();
        irr::f32 midX = (irr::f32)this->getCenter((int)positionComponent->getPosition().X);
        irr::f32 midZ = (irr::f32)this->getCenter((int)positionComponent->getPosition().Z);

        if (moveComponent->getDrop() == true && playerComponent->getCurrentBombNb() > 0 && entity->has<TimerComponent>() == false
            && this->hasBombAtPosition(entityManager, irr::core::vector3df(midX, 20, midZ)) == false) {
            if (playerComponent->getWallPass() == true && this->checkBombPositionWallPass(entityManager, midX, midZ) == false) {
                continue;
            }
            for (auto map : entityManager.each<MapComponent>()) {
                auto mapComponent = map->getComponent<MapComponent>();

                mapComponent->setMap(this->updateMap(mapComponent->getMap(), midX, midZ));
            }
            entityBuilder.createBomb(irr::core::vector3df(irr::f32(midX), 20, irr::f32(midZ)), "../ressources/animated_mesh/bomb/bomb.b3d",
                "../ressources/textures/bomb/bomb.png", entity->getId(), playerComponent->getBombsRange());
            playerComponent->setCurrentBombNb(playerComponent->getCurrentBombNb() - 1);
        }
    }
}
