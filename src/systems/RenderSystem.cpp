/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** RenderSystem
*/

#include "RenderSystem.hpp"
#include "RenderComponent.hpp"
#include "PositionComponent.hpp"
#include "RotationComponent.hpp"

// InputSystem -> moveSystem -> VelocitySystem -> RotationSystem -> MeshSystem -> RenderSystem
/**
 * input -> update les input
 * move -> dit si oui ou non ca doit bouger
 * velocity -> check si oui ou non ca doit bouger -> si oui on change la velicité + l'appliquer à la position
 * rotation -> check si oui ou non ca doit bouger, si oui check la direction dans laquelle il faut aller et change le degré de rotation en fonction
 * mesh -> change la mesh du renderComp en fonction de si oui ou non il faut bouger, le meshComp store les mesh (RUN & STAND) en prenant le texture path en param + store l'état actuel, si l'état à changé, alors change l'état + la mesh
 * ici faudra un truc pour check si oui ou non les perso peuvent move dans la direction voulue, si non, on rétablit la position à la position actuelle du mesh
 * render -> applique rotation + position
 */

void Indie::Systems::RenderSystem::onUpdate(int ticks, EntityManager &entityManager)
{
    for (auto entity : entityManager.each<Indie::Components::RenderComponent, Indie::Components::PositionComponent>()) {
        auto renderComponent = entity->getComponent<Indie::Components::RenderComponent>();
        auto positionComponent = entity->getComponent<Indie::Components::PositionComponent>();
        renderComponent->getMesh()->setPosition(positionComponent->getPosition());
    }
    for (auto entity : entityManager.each<Indie::Components::RenderComponent, Indie::Components::RotationComponent>()) {
        auto renderComponent = entity->getComponent<Indie::Components::RenderComponent>();
        auto rotationComponent = entity->getComponent<Indie::Components::RotationComponent>();
        renderComponent->getMesh()->setRotation(rotationComponent->getAngle());
    }
}
