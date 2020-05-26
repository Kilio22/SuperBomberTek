/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** BombExplosionSystem
*/

#ifndef BOMBEXPLOSIONSYSTEM_HPP_
#define BOMBEXPLOSIONSYSTEM_HPP_

#include "ISystem.hpp"
#include "MapComponent.hpp"

namespace Indie::Systems
{

class BombExplosionSystem : public ISystem
{
    public:
        BombExplosionSystem() = default;
        ~BombExplosionSystem() = default;

        void onUpdate(irr::f32 deltaTime, EntityManager &entityManager) const final;

    private:
        void explodeBomb(std::vector<std::vector<Components::OBJECT>> &map, EntityManager &entityManager, Entity *entity) const;
        void explodeRight(EntityManager &entityManager, std::vector<std::vector<Components::OBJECT>> &map, unsigned int range, int mapX, int mapZ) const;
        void explodeLeft(EntityManager &entityManager, std::vector<std::vector<Components::OBJECT>> &map, unsigned int range, int mapX, int mapZ) const;
        void explodeUp(EntityManager &entityManager, std::vector<std::vector<Components::OBJECT>> &map, unsigned int range, int mapX, int mapZ) const;
        void explodeDown(EntityManager &entityManager, std::vector<std::vector<Components::OBJECT>> &map, unsigned int range, int mapX, int mapZ) const;

        void explodeBox(EntityManager &entityManager, int mapX, int mapZ) const;
        void recursiveExplosion() const;
};

}

#endif /* !BOMBEXPLOSIONSYSTEM_HPP_ */
