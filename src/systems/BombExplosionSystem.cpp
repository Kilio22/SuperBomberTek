/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** BombExplosionSystem
*/

#include "BombExplosionSystem.hpp"
#include "EntityBuilder.hpp"
#include "ServiceLocator.hpp"
#include "IndieException.hpp"

using namespace Indie::Components;

const std::unordered_map<POWERUP_TYPE, std::pair<std::string, std::string>> Indie::Systems::BombExplosionSystem::powerups = {
    { POWERUP_TYPE::BOMB_UP, { "../ressources/static_mesh/effects/bombup.obj", "../ressources/static_mesh/effects/bombup.png" } },
    { POWERUP_TYPE::FIRE_UP, { "../ressources/static_mesh/effects/fireup.obj", "../ressources/static_mesh/effects/fireup.png" } },
    { POWERUP_TYPE::SPEED_UP, { "../ressources/static_mesh/effects/speedup.obj", "../ressources/static_mesh/effects/speedup.png" } },
    { POWERUP_TYPE::WALL_PASS, { "../ressources/static_mesh/effects/wallpass.obj", "../ressources/static_mesh/effects/wallpass.png" } }
};

void Indie::Systems::BombExplosionSystem::onUpdate(irr::f32 deltaTime, EntityManager &entityManager) const
{
    MapComponent *mapComponent = nullptr;
    std::vector<std::vector<OBJECT>> map;

    for (auto entity : entityManager.each<MapComponent>())
        mapComponent = entity->getComponent<MapComponent>();
    if (mapComponent == nullptr)
        throw Exceptions::IndieException(ERROR_STR, "Map was not found.");
    map = mapComponent->getMap();
    for (auto entity : entityManager.each<BombComponent, PositionComponent, TimerComponent>()) {
        auto timer = entity->getComponent<TimerComponent>();

        if (timer->getTimePassed() >= timer->getTimeToEnd())
            this->explodeBomb(map, entityManager, entity);
    }
    mapComponent->setMap(map);
}

void Indie::Systems::BombExplosionSystem::explodeBomb(std::vector<std::vector<OBJECT>> &map, EntityManager &entityManager, Entity *entity) const
{
    auto bomb = entity->getComponent<BombComponent>();
    auto position = entity->getComponent<PositionComponent>();
    auto playerEntity = entityManager.getById(bomb->getIdOwner());
    int mapX = (int)(position->getPosition().X / 20);
    int mapZ = (int)(position->getPosition().Z / 20);
    unsigned int range = bomb->getRange();

    if (bomb->hasExploded() == true)
        return;
    bomb->setExploded(true);
    this->explodeRight(entityManager, map, range, mapX, mapZ);
    this->explodeLeft(entityManager, map, range, mapX, mapZ);
    this->explodeUp(entityManager, map, range, mapX, mapZ);
    this->explodeDown(entityManager, map, range, mapX, mapZ);
    if (playerEntity != nullptr) {
        auto player = playerEntity->getComponent<PlayerComponent>();

        player->setCurrentBombNb(player->getCurrentBombNb() + 1);
    }
}

void Indie::Systems::BombExplosionSystem::explodeRight(EntityManager &entityManager, std::vector<std::vector<OBJECT>> &map, unsigned int range, int mapX, int mapZ) const
{
    auto &entityBuilder = ServiceLocator::getInstance().get<EntityBuilder>();

    if (map[mapZ][mapX + 1] == OBJECT::WALL_OUT || map[mapZ][mapX + 1] == OBJECT::WALL_IN)
        return;
    for (unsigned int i = 0; i <= range; ++i) {
        if (i > 0 && map[mapZ][mapX + i] == OBJECT::BOMB)
            return this->recursiveExplosion(entityManager, map, mapX + i, mapZ);
        if (map[mapZ][mapX + i] == OBJECT::WALL_OUT || map[mapZ][mapX + i] == OBJECT::WALL_IN)
            break;
        if (map[mapZ][mapX + i] == OBJECT::BOX) {
            map[mapZ][mapX + i] = OBJECT::LAVA;
            this->explodeBox(entityManager, mapX + i, mapZ);
            entityBuilder.createLava(irr::core::vector3df((irr::f32)((mapX + i) * 20), 20, (irr::f32)(mapZ * 20)), "../ressources/static_mesh/effects/lava.obj", "../ressources/static_mesh/effects/lava.png", 90.f);
            break;
        }
        map[mapZ][mapX + i] = OBJECT::LAVA;
        entityBuilder.createLava(irr::core::vector3df((irr::f32)((mapX + i) * 20), 20, (irr::f32)(mapZ * 20)), "../ressources/static_mesh/effects/lava.obj", "../ressources/static_mesh/effects/lava.png", 90.f);
    }
}

void Indie::Systems::BombExplosionSystem::explodeLeft(EntityManager &entityManager, std::vector<std::vector<OBJECT>> &map, unsigned int range, int mapX, int mapZ) const
{
    auto &entityBuilder = ServiceLocator::getInstance().get<EntityBuilder>();

    if (map[mapZ][mapX - 1] == OBJECT::WALL_OUT || map[mapZ][mapX - 1] == OBJECT::WALL_IN)
        return;
    for (unsigned int i = 0; i <= range; ++i) {
        if (i > 0 && map[mapZ][mapX - i] == OBJECT::BOMB)
            return this->recursiveExplosion(entityManager, map, mapX - i, mapZ);
        if (map[mapZ][mapX - i] == OBJECT::WALL_OUT || map[mapZ][mapX - i] == OBJECT::WALL_IN)
            break;
        if (map[mapZ][mapX - i] == OBJECT::BOX) {
            map[mapZ][mapX - i] = OBJECT::LAVA;
            this->explodeBox(entityManager, mapX - i, mapZ);
            entityBuilder.createLava(irr::core::vector3df((irr::f32)((mapX - i) * 20), 20, (irr::f32)(mapZ * 20)), "../ressources/static_mesh/effects/lava.obj", "../ressources/static_mesh/effects/lava.png", 270.f);
            break;
        }
        map[mapZ][mapX - i] = OBJECT::LAVA;
        entityBuilder.createLava(irr::core::vector3df((irr::f32)((mapX - i) * 20), 20, (irr::f32)(mapZ * 20)), "../ressources/static_mesh/effects/lava.obj", "../ressources/static_mesh/effects/lava.png", 270.f);
    }
}

void Indie::Systems::BombExplosionSystem::explodeUp(EntityManager &entityManager, std::vector<std::vector<OBJECT>> &map, unsigned int range, int mapX, int mapZ) const
{
    auto &entityBuilder = ServiceLocator::getInstance().get<EntityBuilder>();

    if (map[mapZ + 1][mapX] == OBJECT::WALL_OUT || map[mapZ + 1][mapX] == OBJECT::WALL_IN)
        return;
    for (unsigned int i = 0; i <= range; ++i) {
        if (i > 0 && map[mapZ + i][mapX] == OBJECT::BOMB)
            return this->recursiveExplosion(entityManager, map, mapX, mapZ + i);
        if (map[mapZ + i][mapX] == OBJECT::WALL_OUT || map[mapZ + i][mapX] == OBJECT::WALL_IN)
            break;
        if (map[mapZ + i][mapX] == OBJECT::BOX) {
            map[mapZ + i][mapX] = OBJECT::LAVA;
            this->explodeBox(entityManager, mapX, mapZ + i);
            entityBuilder.createLava(irr::core::vector3df((irr::f32)(mapX * 20), 20, (irr::f32)((mapZ + i) * 20)), "../ressources/static_mesh/effects/lava.obj", "../ressources/static_mesh/effects/lava.png", 180.f);
            break;
        }
        map[mapZ + i][mapX] = OBJECT::LAVA;
        entityBuilder.createLava(irr::core::vector3df((irr::f32)(mapX * 20), 20, (irr::f32)((mapZ + i) * 20)), "../ressources/static_mesh/effects/lava.obj", "../ressources/static_mesh/effects/lava.png", 180.f);
    }
}

void Indie::Systems::BombExplosionSystem::explodeDown(EntityManager &entityManager, std::vector<std::vector<OBJECT>> &map, unsigned int range, int mapX, int mapZ) const
{
    auto &entityBuilder = ServiceLocator::getInstance().get<EntityBuilder>();

    if (map[mapZ - 1][mapX] == OBJECT::WALL_OUT || map[mapZ - 1][mapX] == OBJECT::WALL_IN)
        return;
    for (unsigned int i = 0; i <= range; ++i) {
        if (i > 0 && map[mapZ - i][mapX] == OBJECT::BOMB)
            return this->recursiveExplosion(entityManager, map, mapX, mapZ - i);
        if (map[mapZ - i][mapX] == OBJECT::WALL_OUT || map[mapZ - i][mapX] == OBJECT::WALL_IN)
            break;
        if (map[mapZ - i][mapX] == OBJECT::BOX) {
            map[mapZ - i][mapX] = OBJECT::LAVA;
            this->explodeBox(entityManager, mapX, mapZ - i);
            entityBuilder.createLava(irr::core::vector3df((irr::f32)(mapX * 20), 20, (irr::f32)((mapZ - i) * 20)), "../ressources/static_mesh/effects/lava.obj", "../ressources/static_mesh/effects/lava.png", 180.f);
            break;
        }
        map[mapZ - i][mapX] = OBJECT::LAVA;
        entityBuilder.createLava(irr::core::vector3df((irr::f32)(mapX * 20), 20, (irr::f32)((mapZ - i) * 20)), "../ressources/static_mesh/effects/lava.obj", "../ressources/static_mesh/effects/lava.png", 180.f);
    }
}

void Indie::Systems::BombExplosionSystem::explodeBox(EntityManager &entityManager, int mapX, int mapZ) const
{
    for (auto entity : entityManager.each<WallComponent, PositionComponent>()) {
        if (entity->getComponent<WallComponent>()->getCanBeDestroyed() == false)
            continue;

        auto position = entity->getComponent<PositionComponent>();
        if ((irr::f32)(mapX * 20) == position->getPosition().X && (irr::f32)(mapZ * 20) == position->getPosition().Z) {
            entity->needDestroy();
            this->spawnPowerUp(position->getPosition());
            return;
        }
    }
}

void Indie::Systems::BombExplosionSystem::spawnPowerUp(const irr::core::vector3df &position) const
{
    if (std::rand() % 5 != 0)
        return;
    int index = std::rand() % 4;
    ServiceLocator::getInstance().get<EntityBuilder>().createPowerUp(position, this->powerups.at((POWERUP_TYPE)index).first, this->powerups.at((POWERUP_TYPE)index).second, (POWERUP_TYPE)index);
}

void Indie::Systems::BombExplosionSystem::recursiveExplosion(EntityManager &entityManager, std::vector<std::vector<OBJECT>> &map, int mapX, int mapZ) const
{
    for (auto entity : entityManager.each<BombComponent, PositionComponent, TimerComponent>()) {
        auto position = entity->getComponent<PositionComponent>();

        if ((irr::f32)(mapX * 20) == position->getPosition().X && (irr::f32)(mapZ * 20) == position->getPosition().Z) {
            auto timer = entity->getComponent<TimerComponent>();

            timer->setTimePassed(timer->getTimeToEnd());
            this->explodeBomb(map, entityManager, entity);
        }
    }
}
