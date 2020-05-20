/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** test
*/

#include "EntityManager.hpp"
#include "components/VelocityComponent.hpp"
#include "components/PositionComponent.hpp"

using namespace Indie;
using namespace Components;

int main(void)
{
    EntityManager mnger;

    Entity *entity = mnger.createEntity();
    entity->addComponent<PositionComponent>(0, 0, 0);
    entity = mnger.createEntity();
    entity->addComponent<VelocityComponent>(2000);

    for (auto xd : mnger.each<VelocityComponent>()) {
        std::cout << "Wow" << std::endl;
        std::cout << xd->has<VelocityComponent>() << std::endl;
        std::cout << xd->has<PositionComponent>() << std::endl;
        std::cout << xd->has<VelocityComponent, PositionComponent>() << std::endl;
        xd->addComponent<PositionComponent>(0, 0, 0);
        std::cout << xd->has<VelocityComponent>() << std::endl;
        std::cout << xd->has<PositionComponent>() << std::endl;
        std::cout << xd->has<VelocityComponent, PositionComponent>() << std::endl;
        std::cout << xd->getComponent<VelocityComponent>()->getVelocity() << std::endl;
    }
}
