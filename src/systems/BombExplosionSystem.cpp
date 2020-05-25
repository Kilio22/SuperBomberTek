/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** BombExplosionSystem
*/

#include "BombComponent.hpp"
#include "BombExplosionSystem.hpp"

using namespace Indie::Components;

void Indie::Systems::BombExplosionSystem::onUpdate(irr::f32 deltaTime, EntityManager &entityManager) const
{
    for (auto entity : entityManager.each<BombComponent>()) {
        auto bomb = entity->getComponent<BombComponent>();

        bomb->ticks += deltaTime;
        if (bomb->exploded == false && bomb->ticks >= 3) {
            std::cout << "BimBamBoum" << std::endl;
            bomb->exploded = true;
        }
    }
}
