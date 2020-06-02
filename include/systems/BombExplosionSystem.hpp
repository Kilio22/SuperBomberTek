/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** BombExplosionSystem
*/

#ifndef BOMBEXPLOSIONSYSTEM_HPP_
#define BOMBEXPLOSIONSYSTEM_HPP_

#include "Components.h"
#include "ISystem.hpp"
#include <unordered_map>

namespace Indie::Systems
{
    class BombExplosionSystem : public ISystem
    {
    public:
        BombExplosionSystem() = default;
        ~BombExplosionSystem() = default;

        void onUpdate(irr::f32 deltaTime, EntityManager &entityManager) const final;

    private:
        static const std::unordered_map<Components::POWERUP_TYPE, std::pair<std::string, std::string>> powerups;

        void explodeBombs(std::vector<std::vector<Components::OBJECT>> &map, EntityManager &entityManager, Entity *entity) const;
        bool explodeBomb(std::vector<std::vector<Components::OBJECT>> &map, EntityManager &entityManager, Entity *entity, int mapX, int mapZ, float angle, bool allowRecursiveExplosions) const;

        void explodeBox(EntityManager &entityManager, Entity *playerEntity, int mapX, int mapZ) const;
        void recursiveExplosion(std::vector<std::vector<Components::OBJECT>> &map, EntityManager &entityManager, int mapX, int mapZ) const;

        void spawnPowerUp(const irr::core::vector3df &position) const;
    };

}

#endif /* !BOMBEXPLOSIONSYSTEM_HPP_ */
