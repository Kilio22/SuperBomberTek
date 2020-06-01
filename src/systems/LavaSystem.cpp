/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** LavaSystem
*/

#include "LavaSystem.hpp"

using namespace Indie::Components;

void Indie::Systems::LavaSystem::onUpdate(irr::f32, EntityManager &entityManager) const
{
    MapComponent *mapComponent = nullptr;
    std::vector<std::vector<OBJECT>> map;

    for (auto entity : entityManager.each<MapComponent>())
        mapComponent = entity->getComponent<MapComponent>();
    if (mapComponent == nullptr)
        throw Exceptions::IndieException(ERROR_STR, "Map was not found.");
    map = mapComponent->getMap();
    for (auto entity : entityManager.each<KillComponent, PositionComponent, TimerComponent>()) {
        auto timer = entity->getComponent<TimerComponent>();

        if (timer->getTimePassed() >= timer->getTimeToEnd())
            this->removeElementFromMap(map, entity);
    }
    mapComponent->setMap(map);
}

void Indie::Systems::LavaSystem::removeElementFromMap(std::vector<std::vector<OBJECT>> &map, Entity *entity) const
{
    auto position = entity->getComponent<PositionComponent>();
    int mapX = (int)(position->getPosition().X / 20);
    int mapZ = (int)(position->getPosition().Z / 20);

    map[mapZ][mapX] = OBJECT::VOID;
}