/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** BombSystem
*/

#include "BombSystem.hpp"
#include "Components.h"
#include "EntityBuilder.hpp"

bool Indie::Systems::BombSystem::hasBombAtPosition(EntityManager &entityManager, irr::core::vector3df position) const
{
    for (auto bomb : entityManager.each<Components::RenderComponent, Components::PositionComponent, Components::BombComponent>()) {
        auto positionComponent = bomb->getComponent<Components::PositionComponent>();
        if (positionComponent->getPosition() == position)
            return true;
    }
    return false;
}

int Indie::Systems::BombSystem::getCenter(int value) const
{
    if (value % 20 < 10) {
        return value - (value % 20);
    } else {
        return value + 20 - (value % 20);
    }
}

void Indie::Systems::BombSystem::onUpdate(irr::f32 deltaTime, EntityManager &entityManager) const
{
    auto &entityBuilder = ServiceLocator::getInstance().get<EntityBuilder>();

    for (auto entity : entityManager.each<Components::MoveComponent, Components::RenderComponent, Components::PositionComponent, Components::VelocityComponent, Components::MeshComponent>()) {
        auto positionComponent = entity->getComponent<Components::PositionComponent>();
        auto moveComponent = entity->getComponent<Components::MoveComponent>();
        irr::f32 midX = (irr::f32)this->getCenter((int)positionComponent->getPosition().X);
        irr::f32 midZ = (irr::f32)this->getCenter((int)positionComponent->getPosition().Z);

        if (moveComponent->getDrop() == true && this->hasBombAtPosition(entityManager, irr::core::vector3df(midX, 20, midZ)) == false) {
            entityBuilder.createBomb( irr::core::vector3df(irr::f32(midX), 20, irr::f32(midZ)), "../ressources/animated_mesh/bomb/bomb.b3d", "../ressources/textures/bomb/bomb.png");
        }
    }
}
