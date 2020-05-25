/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** BombExplosionSystem
*/

#include "BombExplosionSystem.hpp"
#include "EntityBuilder.hpp"
#include "ServiceLocator.hpp"

using namespace Indie::Components;

void Indie::Systems::BombExplosionSystem::onUpdate(irr::f32 deltaTime, EntityManager &entityManager) const
{
    std::vector<std::vector<OBJECT>> map;

    for (auto entity : entityManager.each<MapComponent>())
        map = entity->getComponent<MapComponent>()->getMap();
    for (auto entity : entityManager.each<BombComponent, PositionComponent, TimerComponent>()) {
        auto timer = entity->getComponent<TimerComponent>();

        if (timer->getTimePassed() >= timer->getTimeToEnd()) {
            std::cout << "BimBamBoum" << std::endl;
            this->explodeBomb(map, entityManager, entity);
        }
    }
}

void Indie::Systems::BombExplosionSystem::explodeBomb(std::vector<std::vector<OBJECT>> &map, EntityManager &entityManager, Entity *entity) const
{
    auto bomb = entity->getComponent<BombComponent>();
    auto position = entity->getComponent<PositionComponent>();
    auto player = entityManager.getById(bomb->getIdOwner())->getComponent<PlayerComponent>();
    int mapX = position->getPosition().X / 20;
    int mapZ = position->getPosition().Z / 20;
    u_int32_t range = bomb->getRange();

    this->explodeRight(map, range, mapX, mapZ);
    this->explodeLeft(map, range, mapX, mapZ);
    this->explodeUp(map, range, mapX, mapZ);
    this->explodeDown(map, range, mapX, mapZ);
    player->setCurrentBombNb(player->getCurrentBombNb() + 1);
}

void Indie::Systems::BombExplosionSystem::explodeRight(std::vector<std::vector<OBJECT>> &map, u_int32_t range, int mapX, int mapZ) const
{
    auto &entityBuilder = ServiceLocator::getInstance().get<EntityBuilder>();

    if (map[mapX + 1][mapZ] == OBJECT::WALL_OUT || map[mapX + 1][mapZ] == OBJECT::WALL_IN)
        return;
    for (u_int32_t i = 0; i <= range; ++i) {
        if (map[mapX + i][mapZ] == OBJECT::WALL_OUT || map[mapX + i][mapZ] == OBJECT::WALL_IN)
            break;
        if (map[mapX + i][mapZ] == OBJECT::BOX) {
            map[mapX + i][mapZ] = OBJECT::LAVA;
            // remove box
            entityBuilder.createLava(irr::core::vector3df((irr::f32)((mapX + i) * 20), 20, (irr::f32)(mapZ * 20)), "../ressources/static_mesh/effects/lava.obj", "../ressources/static_mesh/effects/lava.png", 90.f);
            break;
        }
        map[mapX + i][mapZ] = OBJECT::LAVA;
        entityBuilder.createLava(irr::core::vector3df((irr::f32)((mapX + i) * 20), 20, (irr::f32)(mapZ * 20)), "../ressources/static_mesh/effects/lava.obj", "../ressources/static_mesh/effects/lava.png", 90.f);
    }
}

void Indie::Systems::BombExplosionSystem::explodeLeft(std::vector<std::vector<OBJECT>> &map, u_int32_t range, int mapX, int mapZ) const
{
    auto &entityBuilder = ServiceLocator::getInstance().get<EntityBuilder>();

    if (map[mapX - 1][mapZ] == OBJECT::WALL_OUT || map[mapX - 1][mapZ] == OBJECT::WALL_IN)
        return;
    for (u_int32_t i = 0; i <= range; ++i) {
        if (map[mapX - i][mapZ] == OBJECT::WALL_OUT || map[mapX - i][mapZ] == OBJECT::WALL_IN)
            break;
        if (map[mapX - i][mapZ] == OBJECT::BOX) {
            map[mapX - i][mapZ] = OBJECT::LAVA;
            // remove box
            entityBuilder.createLava(irr::core::vector3df((irr::f32)((mapX - i) * 20), 20, (irr::f32)(mapZ * 20)), "../ressources/static_mesh/effects/lava.obj", "../ressources/static_mesh/effects/lava.png", 270.f);
            break;
        }
        map[mapX - i][mapZ] = OBJECT::LAVA;
        entityBuilder.createLava(irr::core::vector3df((irr::f32)((mapX - i) * 20), 20, (irr::f32)(mapZ * 20)), "../ressources/static_mesh/effects/lava.obj", "../ressources/static_mesh/effects/lava.png", 270.f);
    }
}

void Indie::Systems::BombExplosionSystem::explodeUp(std::vector<std::vector<OBJECT>> &map, u_int32_t range, int mapX, int mapZ) const
{
    auto &entityBuilder = ServiceLocator::getInstance().get<EntityBuilder>();

    if (map[mapX][mapZ + 1] == OBJECT::WALL_OUT || map[mapX][mapZ + 1] == OBJECT::WALL_IN)
        return;
    for (u_int32_t i = 0; i <= range; ++i) {
        if (map[mapX][mapZ + i] == OBJECT::WALL_OUT || map[mapX][mapZ + i] == OBJECT::WALL_IN)
            break;
        if (map[mapX][mapZ + i] == OBJECT::BOX) {
            map[mapX][mapZ + i] = OBJECT::LAVA;
            // remove box
            entityBuilder.createLava(irr::core::vector3df((irr::f32)(mapX * 20), 20, (irr::f32)((mapZ + i) * 20)), "../ressources/static_mesh/effects/lava.obj", "../ressources/static_mesh/effects/lava.png", 180.f);
            break;
        }
        map[mapX][mapZ + i] = OBJECT::LAVA;
        entityBuilder.createLava(irr::core::vector3df((irr::f32)(mapX * 20), 20, (irr::f32)((mapZ + i) * 20)), "../ressources/static_mesh/effects/lava.obj", "../ressources/static_mesh/effects/lava.png", 180.f);
    }
}

void Indie::Systems::BombExplosionSystem::explodeDown(std::vector<std::vector<OBJECT>> &map, u_int32_t range, int mapX, int mapZ) const
{
    auto &entityBuilder = ServiceLocator::getInstance().get<EntityBuilder>();

    if (map[mapX][mapZ - 1] == OBJECT::WALL_OUT || map[mapX][mapZ - 1] == OBJECT::WALL_IN)
        return;
    for (u_int32_t i = 0; i <= range; ++i) {
        if (map[mapX][mapZ - i] == OBJECT::WALL_OUT || map[mapX][mapZ - i] == OBJECT::WALL_IN)
            break;
        if (map[mapX][mapZ - i] == OBJECT::BOX) {
            map[mapX][mapZ - i] = OBJECT::LAVA;
            // remove box
            entityBuilder.createLava(irr::core::vector3df((irr::f32)(mapX * 20), 20, (irr::f32)((mapZ - i) * 20)), "../ressources/static_mesh/effects/lava.obj", "../ressources/static_mesh/effects/lava.png", 180.f);
            break;
        }
        map[mapX][mapZ - i] = OBJECT::LAVA;
        entityBuilder.createLava(irr::core::vector3df((irr::f32)(mapX * 20), 20, (irr::f32)((mapZ - i) * 20)), "../ressources/static_mesh/effects/lava.obj", "../ressources/static_mesh/effects/lava.png", 180.f);
    }
}
