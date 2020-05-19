/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** VelocitySystem
*/

#include "VelocitySystem.hpp"
#include "PositionComponent.hpp"
#include "VelocityComponent.hpp"
#include "InputComponent.hpp"
#include "MoveComponent.hpp"

void Indie::Systems::VelocitySystem::onUpdate(int ticks, EntityManager &entityManager)
{
    auto entities = entityManager.getEntitiesByComponents(2); // Faut get les entity qui bougent (avec input + position + move + velocity bien sur xd)

    for (auto &entity : entities) {
        auto moveComp = entity.getComponent<Indie::Components::MoveComponent>(42);
        auto posComp = entity.getComponent<Indie::Components::PositionComponent>(42);
        auto velComp = entity.getComponent<Indie::Components::VelocityComponent>(42);
        velComp->setVelocity(0);
        if (moveComp->getUp() == true) {
            velComp->setVelocity(1);

        }
    }
}