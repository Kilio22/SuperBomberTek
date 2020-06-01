/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** TimerStopSystem
*/

#include "TimerStopSystem.hpp"
#include "TimerComponent.hpp"
#include "PositionComponent.hpp"
#include "BombComponent.hpp"
#include "MapComponent.hpp"

using namespace Indie::Components;

void Indie::Systems::TimerStopSystem::onUpdate(irr::f32 deltaTime, EntityManager &entityManager) const
{
    MapComponent *mapComponent;
    std::vector<std::vector<Indie::Components::OBJECT>> map;

    for (auto entity : entityManager.each<MapComponent>()) {
        mapComponent = entity->getComponent<MapComponent>();
        map = mapComponent->getMap();
    }

    for (auto entity : entityManager.each<TimerComponent, PositionComponent>()) {
        auto timer = entity->getComponent<TimerComponent>();
        auto position = entity->getComponent<PositionComponent>();

        int posX = (int)position->getPosition().X / 20;
        int posZ = (int)position->getPosition().Z / 20;

        if (timer->getTimePassed() >= timer->getTimeToEnd()) {
            if (map[posZ][posX] == OBJECT::LAVA && !entity->has<BombComponent>())
                map[posZ][posX] = OBJECT::VOID;
            entity->needDestroy();
        }
    }
    mapComponent->setMap(map);
}
