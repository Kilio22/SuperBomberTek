/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** BombDropSystem
*/

#include "BombDropSystem.hpp"
#include "Components.h"
#include "EntityBuilder.hpp"
#include "SoundManager.hpp"

using namespace Indie::Components;

std::vector<std::vector<Indie::Components::OBJECT>> Indie::Systems::BombDropSystem::updateMap(
    std::vector<std::vector<Components::OBJECT>> currentMap, irr::f32 midX, irr::f32 midZ) const
{
    currentMap[(int)(midZ / 20)][(int)(midX / 20)] = OBJECT::BOMB;
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
    auto mapComponent = entityManager.getUniqueEntity<MapComponent>()->getComponent<MapComponent>();
    auto array = mapComponent->getMap();

    for (int i = 0; i < (int)mapComponent->getDimension().Y; i++) {
        for (int j = 0; j < (int)mapComponent->getDimension().X; j++) {
            if (array[i][j] == OBJECT::VOID && j * 20 == midX && i * 20 == midZ) {
                return true;
            }
        }
    }
    return false;
}

void Indie::Systems::BombDropSystem::onUpdate(irr::f32, EntityManager &entityManager) const
{
    auto &entityBuilder = ServiceLocator::getInstance().get<EntityBuilder>();

    for (auto entity : entityManager.each<MoveComponent, PositionComponent, PlayerComponent>()) {
        auto moveComponent = entity->getComponent<MoveComponent>();
        auto positionComponent = entity->getComponent<PositionComponent>();
        auto playerComponent = entity->getComponent<PlayerComponent>();
        irr::f32 midX = (irr::f32)this->getCenter((int)positionComponent->getPosition().X);
        irr::f32 midZ = (irr::f32)this->getCenter((int)positionComponent->getPosition().Z);

        if (moveComponent->getDrop() == true && playerComponent->getCurrentBombNb() > 0 && entity->has<TimerComponent>() == false
            && this->hasBombAtPosition(entityManager, { midX, 20.f, midZ }) == false) {
            if (playerComponent->getWallPass() == true && this->checkBombPositionWallPass(entityManager, (int)midX, (int)midZ) == false) {
                continue;
            }
            auto mapComponent = entityManager.getUniqueEntity<MapComponent>()->getComponent<MapComponent>();

            mapComponent->setMap(this->updateMap(mapComponent->getMap(), midX, midZ));
            ServiceLocator::getInstance().get<SoundManager>().playPitchedSound(
                "bomb_drop", positionComponent->getPosition().X, positionComponent->getPosition().Y, positionComponent->getPosition().Z);
            entityBuilder.createBomb({ midX, 20.f, midZ }, "../ressources/animated_mesh/bomb/bomb.b3d", "../ressources/textures/bomb/bomb.png",
                entity->getId(), playerComponent->getBombsRange());
            playerComponent->setCurrentBombNb(playerComponent->getCurrentBombNb() - 1);
        }
    }
}
