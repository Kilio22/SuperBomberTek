/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** RenderSystem
*/

#include "RenderSystem.hpp"
#include "RenderComponent.hpp"
#include "PositionComponent.hpp"

void Indie::System::RenderSystem::onUpdate(int ticks, EntityManager &entityManager)
{
    auto entities = entityManager.getEntitiesByComponents(0);

    for (auto &entity : entities) {
        auto rendComp = entity.getComponent<Indie::Components::RenderComponent>(0);
        auto posComp = entity.getComponent<Indie::Components::PositionComponent>(1);

        printf("%p\n", *posComp);
        printf("%f %f %f\n", posComp->getPosition().X, posComp->getPosition().Y, posComp->getPosition().Z);
        rendComp->getMesh()->setPosition(posComp->getPosition());
    }
}
