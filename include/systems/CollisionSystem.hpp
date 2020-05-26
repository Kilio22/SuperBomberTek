/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** CollisionSystem
*/

#ifndef COLLISIONSYSTEM_HPP_
#define COLLISIONSYSTEM_HPP_

#include "ISystem.hpp"
#include "Components.h"

namespace Indie::Systems
{
    class CollisionSystem : public ISystem
    {
        public:
            CollisionSystem() = default;
            ~CollisionSystem() = default;

            void onUpdate(irr::f32 deltaTime, EntityManager &entityManager) const final;

        private:

            template <typename... Args>
            bool checkCollisionWithEntities(EntityManager &entityManager, const irr::core::aabbox3df &characterBoundingBox) const
            {
                for (Entity *entity : entityManager.each<Args...>()) {
                    Components::RenderComponent *renderComponent = entity->getComponent<Components::RenderComponent>();

                    if (characterBoundingBox.intersectsWithBox(renderComponent->getMesh()->getTransformedBoundingBox()) == true) {
                        return true;
                    }
                }
                return false;
            }

            bool checkCollisionWithCharacters(EntityManager &entityManager, const irr::core::aabbox3df &characterBoundingBox, const irr::core::vector3df &currentCharacterPosition) const;
            bool checkCollisionWithBombs(EntityManager &entityManager, const irr::core::aabbox3df &characterBoundingBox, int characterId) const;
            bool checkCollisionWithPowerUp(EntityManager &entityManager, const irr::core::aabbox3df &characterBoundingBox, Components::POWERUP_TYPE type) const;
            void checkCollisionWithPowerUps(EntityManager &entityManager, const irr::core::aabbox3df &characterBoundingBox, Components::PlayerComponent *playerComponent) const;
            irr::core::aabbox3df updateCharacterBoundingBox(irr::core::aabbox3df characterBoundingBox, const irr::core::vector3df &currentPosition, const irr::core::vector3df &wantedPosition) const;
    };
} // namespace Indie::Systems


#endif /* !COLLISIONSYSTEM_HPP_ */
