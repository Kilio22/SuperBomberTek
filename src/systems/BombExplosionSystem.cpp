/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** BombExplosionSystem
*/

#include "BombExplosionSystem.hpp"
#include "EntityBuilder.hpp"
#include "IndieException.hpp"
#include "ServiceLocator.hpp"

using namespace Indie::Components;

const std::unordered_map<POWERUP_TYPE, std::pair<std::string, std::string>> Indie::Systems::BombExplosionSystem::powerups
    = { { POWERUP_TYPE::BOMB_UP, { "../ressources/static_mesh/effects/bombup.obj", "../ressources/static_mesh/effects/bombup.png" } },
          { POWERUP_TYPE::FIRE_UP, { "../ressources/static_mesh/effects/fireup.obj", "../ressources/static_mesh/effects/fireup.png" } },
          { POWERUP_TYPE::SPEED_UP, { "../ressources/static_mesh/effects/speedup.obj", "../ressources/static_mesh/effects/speedup.png" } },
          { POWERUP_TYPE::WALL_PASS, { "../ressources/static_mesh/effects/wallpass.obj", "../ressources/static_mesh/effects/wallpass.png" } } };

void Indie::Systems::BombExplosionSystem::onUpdate(irr::f32, EntityManager &entityManager) const
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
            this->explodeBombs(map, entityManager, entity);
    }
    mapComponent->setMap(map);
}

void Indie::Systems::BombExplosionSystem::explodeBombs(std::vector<std::vector<OBJECT>> &map, EntityManager &entityManager, Entity *entity) const
{
    auto bomb = entity->getComponent<BombComponent>();
    auto position = entity->getComponent<PositionComponent>();
    auto playerEntity = entityManager.getById(bomb->getIdOwner());
    auto player = playerEntity == nullptr ? nullptr : playerEntity->getComponent<PlayerComponent>();
    int mapX = (int)(position->getPosition().X / 20);
    int mapZ = (int)(position->getPosition().Z / 20);
    unsigned int range = bomb->getRange();
    bool right = true;
    bool left = true;
    bool up = true;
    bool down = true;

    if (bomb->hasExploded() == true || player == nullptr)
        return;
    bomb->setExploded(true);
    for (unsigned int i = 0; i <= range; ++i) {
        if (right == true && map[mapZ][mapX + 1] != OBJECT::WALL_OUT && map[mapZ][mapX + 1] != OBJECT::WALL_IN)
            right = this->explodeBomb(map, entityManager, playerEntity, mapX + i, mapZ, 90.0f, i > 0);
        if (left == true && map[mapZ][mapX - 1] != OBJECT::WALL_OUT && map[mapZ][mapX - 1] != OBJECT::WALL_IN)
            left = this->explodeBomb(map, entityManager, playerEntity, mapX - i, mapZ, 270.0f, i > 0);
        if (up == true && map[mapZ + 1][mapX] != OBJECT::WALL_OUT && map[mapZ + 1][mapX] != OBJECT::WALL_IN)
            up = this->explodeBomb(map, entityManager, playerEntity, mapX, mapZ + i, 0.0f, i > 0);
        if (down == true && map[mapZ - 1][mapX] != OBJECT::WALL_OUT && map[mapZ - 1][mapX] != OBJECT::WALL_IN)
            down = this->explodeBomb(map, entityManager, playerEntity, mapX, mapZ - i, 180.0f, i > 0);
    }
    player->setCurrentBombNb(player->getCurrentBombNb() + 1);
}

bool Indie::Systems::BombExplosionSystem::explodeBomb(
    std::vector<std::vector<OBJECT>> &map, EntityManager &entityManager, Entity *playerEntity, int mapX, int mapZ, float angle, bool allowRecursiveExplosions) const
{
    auto &entityBuilder = ServiceLocator::getInstance().get<EntityBuilder>();

    if (allowRecursiveExplosions == true && map[mapZ][mapX] == OBJECT::BOMB) {
        this->recursiveExplosion(map, entityManager, mapX, mapZ);
        return true;
    }
    if (map[mapZ][mapX] == OBJECT::WALL_OUT || map[mapZ][mapX] == OBJECT::WALL_IN)
        return false;
    if (map[mapZ][mapX] == OBJECT::BOX) {
        map[mapZ][mapX] = OBJECT::LAVA;
        this->explodeBox(entityManager, playerEntity, mapX, mapZ);
        entityBuilder.createLava({ (irr::f32)(mapX * 20), 20, (irr::f32)(mapZ * 20) }, "../ressources/static_mesh/effects/lava.obj",
            "../ressources/static_mesh/effects/lava.png", angle, playerEntity->getId());
        return false;
    }
    map[mapZ][mapX] = OBJECT::LAVA;
    entityBuilder.createLava({ (irr::f32)(mapX * 20), 20, (irr::f32)(mapZ * 20) }, "../ressources/static_mesh/effects/lava.obj",
        "../ressources/static_mesh/effects/lava.png", angle, playerEntity->getId());
    return true;
}

// void Indie::Systems::BombExplosionSystem::explodeRight(
//     EntityManager &entityManager, std::vector<std::vector<OBJECT>> &map, int ownerId, unsigned int range, int mapX, int mapZ) const
// {
//     auto &entityBuilder = ServiceLocator::getInstance().get<EntityBuilder>();

//     if (map[mapZ][mapX + 1] == OBJECT::WALL_OUT || map[mapZ][mapX + 1] == OBJECT::WALL_IN)
//         return;
//     for (unsigned int i = 0; i <= range; ++i) {
//         if (i > 0 && map[mapZ][mapX + i] == OBJECT::BOMB)
//             return this->recursiveExplosion(entityManager, map, mapX + i, mapZ);
//         if (map[mapZ][mapX + i] == OBJECT::WALL_OUT || map[mapZ][mapX + i] == OBJECT::WALL_IN)
//             break;
//         if (map[mapZ][mapX + i] == OBJECT::BOX) {
//             map[mapZ][mapX + i] = OBJECT::LAVA;
//             this->explodeBox(entityManager, mapX + i, mapZ);
//             entityBuilder.createLava(irr::core::vector3df((irr::f32)((mapX + i) * 20), 20, (irr::f32)(mapZ * 20)),
//                 "../ressources/static_mesh/effects/lava.obj", "../ressources/static_mesh/effects/lava.png", 90.f, ownerId);
//             break;
//         }
//         map[mapZ][mapX + i] = OBJECT::LAVA;
//         entityBuilder.createLava(irr::core::vector3df((irr::f32)((mapX + i) * 20), 20, (irr::f32)(mapZ * 20)),
//             "../ressources/static_mesh/effects/lava.obj", "../ressources/static_mesh/effects/lava.png", 90.f, ownerId);
//     }
// }

// void Indie::Systems::BombExplosionSystem::explodeLeft(
//     EntityManager &entityManager, std::vector<std::vector<OBJECT>> &map, int ownerId, unsigned int range, int mapX, int mapZ) const
// {
//     auto &entityBuilder = ServiceLocator::getInstance().get<EntityBuilder>();

//     if (map[mapZ][mapX - 1] == OBJECT::WALL_OUT || map[mapZ][mapX - 1] == OBJECT::WALL_IN)
//         return;
//     for (unsigned int i = 0; i <= range; ++i) {
//         if (i > 0 && map[mapZ][mapX - i] == OBJECT::BOMB)
//             return this->recursiveExplosion(entityManager, map, mapX - i, mapZ);
//         if (map[mapZ][mapX - i] == OBJECT::WALL_OUT || map[mapZ][mapX - i] == OBJECT::WALL_IN)
//             break;
//         if (map[mapZ][mapX - i] == OBJECT::BOX) {
//             map[mapZ][mapX - i] = OBJECT::LAVA;
//             this->explodeBox(entityManager, mapX - i, mapZ);
//             entityBuilder.createLava(irr::core::vector3df((irr::f32)((mapX - i) * 20), 20, (irr::f32)(mapZ * 20)),
//                 "../ressources/static_mesh/effects/lava.obj", "../ressources/static_mesh/effects/lava.png", 270.f, ownerId);
//             break;
//         }
//         map[mapZ][mapX - i] = OBJECT::LAVA;
//         entityBuilder.createLava(irr::core::vector3df((irr::f32)((mapX - i) * 20), 20, (irr::f32)(mapZ * 20)),
//             "../ressources/static_mesh/effects/lava.obj", "../ressources/static_mesh/effects/lava.png", 270.f, ownerId);
//     }
// }

// void Indie::Systems::BombExplosionSystem::explodeUp(
//     EntityManager &entityManager, std::vector<std::vector<OBJECT>> &map, int ownerId, unsigned int range, int mapX, int mapZ) const
// {
//     auto &entityBuilder = ServiceLocator::getInstance().get<EntityBuilder>();

//     if (map[mapZ + 1][mapX] == OBJECT::WALL_OUT || map[mapZ + 1][mapX] == OBJECT::WALL_IN)
//         return;
//     for (unsigned int i = 0; i <= range; ++i) {
//         if (i > 0 && map[mapZ + i][mapX] == OBJECT::BOMB)
//             return this->recursiveExplosion(entityManager, map, mapX, mapZ + i);
//         if (map[mapZ + i][mapX] == OBJECT::WALL_OUT || map[mapZ + i][mapX] == OBJECT::WALL_IN)
//             break;
//         if (map[mapZ + i][mapX] == OBJECT::BOX) {
//             map[mapZ + i][mapX] = OBJECT::LAVA;
//             this->explodeBox(entityManager, mapX, mapZ + i);
//             entityBuilder.createLava(irr::core::vector3df((irr::f32)(mapX * 20), 20, (irr::f32)((mapZ + i) * 20)),
//                 "../ressources/static_mesh/effects/lava.obj", "../ressources/static_mesh/effects/lava.png", 0.f, ownerId);
//             break;
//         }
//         map[mapZ + i][mapX] = OBJECT::LAVA;
//         entityBuilder.createLava(irr::core::vector3df((irr::f32)(mapX * 20), 20, (irr::f32)((mapZ + i) * 20)),
//             "../ressources/static_mesh/effects/lava.obj", "../ressources/static_mesh/effects/lava.png", 0.f, ownerId);
//     }
// }

// void Indie::Systems::BombExplosionSystem::explodeDown(
//     EntityManager &entityManager, std::vector<std::vector<OBJECT>> &map, int ownerId, unsigned int range, int mapX, int mapZ) const
// {
//     auto &entityBuilder = ServiceLocator::getInstance().get<EntityBuilder>();

//     if (map[mapZ - 1][mapX] == OBJECT::WALL_OUT || map[mapZ - 1][mapX] == OBJECT::WALL_IN)
//         return;
//     for (unsigned int i = 0; i <= range; ++i) {
//         if (i > 0 && map[mapZ - i][mapX] == OBJECT::BOMB)
//             return this->recursiveExplosion(entityManager, map, mapX, mapZ - i);
//         if (map[mapZ - i][mapX] == OBJECT::WALL_OUT || map[mapZ - i][mapX] == OBJECT::WALL_IN)
//             break;
//         if (map[mapZ - i][mapX] == OBJECT::BOX) {
//             map[mapZ - i][mapX] = OBJECT::LAVA;
//             this->explodeBox(entityManager, mapX, mapZ - i);
//             entityBuilder.createLava(irr::core::vector3df((irr::f32)(mapX * 20), 20, (irr::f32)((mapZ - i) * 20)),
//                 "../ressources/static_mesh/effects/lava.obj", "../ressources/static_mesh/effects/lava.png", 180.f, ownerId);
//             break;
//         }
//         map[mapZ - i][mapX] = OBJECT::LAVA;
//         entityBuilder.createLava(irr::core::vector3df((irr::f32)(mapX * 20), 20, (irr::f32)((mapZ - i) * 20)),
//             "../ressources/static_mesh/effects/lava.obj", "../ressources/static_mesh/effects/lava.png", 180.f, ownerId);
//     }
// }

void Indie::Systems::BombExplosionSystem::explodeBox(EntityManager &entityManager, Entity *playerEntity, int mapX, int mapZ) const
{
    for (auto entity : entityManager.each<WallComponent, PositionComponent>()) {
        if (entity->getComponent<WallComponent>()->getCanBeDestroyed() == false)
            continue;

        auto position = entity->getComponent<PositionComponent>();
        if ((irr::f32)(mapX * 20) == position->getPosition().X && (irr::f32)(mapZ * 20) == position->getPosition().Z) {
            auto player = playerEntity->getComponent<PlayerComponent>();

            player->setXpCount(player->getXpCount() + 10);
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
    int index = std::rand() % (int)POWERUP_TYPE::NONE;
    if (index == (int)POWERUP_TYPE::WALL_PASS) {
        if (std::rand() % 2 != 0)
            return;
    }
    ServiceLocator::getInstance().get<EntityBuilder>().createPowerUp(
        position, this->powerups.at((POWERUP_TYPE)index).first, this->powerups.at((POWERUP_TYPE)index).second, (POWERUP_TYPE)index);
}

void Indie::Systems::BombExplosionSystem::recursiveExplosion(
    std::vector<std::vector<OBJECT>> &map, EntityManager &entityManager, int mapX, int mapZ) const
{
    for (auto entity : entityManager.each<BombComponent, PositionComponent, TimerComponent>()) {
        auto position = entity->getComponent<PositionComponent>();

        if ((irr::f32)(mapX * 20) == position->getPosition().X && (irr::f32)(mapZ * 20) == position->getPosition().Z) {
            auto timer = entity->getComponent<TimerComponent>();

            timer->setTimePassed(timer->getTimeToEnd());
            this->explodeBombs(map, entityManager, entity);
        }
    }
}
