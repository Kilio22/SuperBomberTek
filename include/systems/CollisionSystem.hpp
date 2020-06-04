/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** CollisionSystem
*/

#ifndef COLLISIONSYSTEM_HPP_
#define COLLISIONSYSTEM_HPP_

#include "Components.h"
#include "ISystem.hpp"

namespace Indie::Systems
{
    class CollisionSystem : public ISystem
    {
    public:
        CollisionSystem() = default;
        ~CollisionSystem() = default;

        void onUpdate(irr::f32 deltaTime, EntityManager &entityManager) const final;

    private:
        template <class T>
        T *checkCollisionWithEffect(EntityManager &entityManager, const irr::core::aabbox3df &characterBoundingBox) const
        {
            for (Entity *entity : entityManager.each<Components::RenderComponent, T>()) {
                T *TComponent = entity->getComponent<T>();
                Components::RenderComponent *renderComponent = entity->getComponent<Components::RenderComponent>();

                if (renderComponent->getMesh()->getTransformedBoundingBox().intersectsWithBox(characterBoundingBox) == true) {
                    entity->needDestroy();
                    return TComponent;
                }
            }
            return nullptr;
        }

        bool checkCollisionWithCharacters(EntityManager &entityManager, const irr::core::aabbox3df &characterBoundingBox,
            const irr::core::vector3df &currentCharacterPosition) const;
        bool checkCollisionWithBombs(EntityManager &entityManager, const irr::core::aabbox3df &characterBoundingBox, int characterId) const;
        void checkCollisionWithPowerUps(
            EntityManager &entityManager, const irr::core::aabbox3df &characterBoundingBox, Components::PlayerComponent *playerComponent) const;
        void checkCollisionWithPowerDowns(
            EntityManager &entityManager, const irr::core::aabbox3df &characterBoundingBox, Components::PlayerComponent *playerComponent) const;
        irr::core::aabbox3df updateCharacterBoundingBox(
            irr::core::aabbox3df characterBoundingBox, const irr::core::vector3df &currentPosition, const irr::core::vector3df &wantedPosition) const;
        bool checkCollisionWithWalls(
            EntityManager &entityManager, const irr::core::aabbox3df &characterBoundingBox, Components::PlayerComponent *playerComponent) const;
        std::pair<bool, int> checkCollisionWithKillingEntities(
            EntityManager &entityManager, const irr::core::aabbox3df &characterBoundingBox, Components::PlayerComponent *playerComponent) const;
    };
} // namespace Indie::Systems

#endif /* !COLLISIONSYSTEM_HPP_ */
