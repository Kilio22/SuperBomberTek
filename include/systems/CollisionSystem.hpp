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
            template <typename... Args>
            bool checkCollisionWithEntities(
                EntityManager &entityManager, const irr::core::aabbox3df &characterBoundingBox, Components::PlayerComponent *playerComponent) const
            {
                bool ret_val = false;

                for (Entity *entity : entityManager.each<Args...>()) {
                    Components::RenderComponent *renderComponent = entity->getComponent<Components::RenderComponent>();
                    Components::WallComponent *wallComponent = entity->getComponent<Components::WallComponent>();

                    if (characterBoundingBox.intersectsWithBox(renderComponent->getMesh()->getTransformedBoundingBox()) == true) {
                        if (wallComponent != nullptr && wallComponent->getCanBeDestroyed() == true && playerComponent->getWallPass() == true && ret_val != true) {
                            ret_val = false;
                            continue;
                        }
                        ret_val = true;
                    }
                }
                return ret_val;
            }

            bool checkCollisionWithCharacters(EntityManager &entityManager, const irr::core::aabbox3df &characterBoundingBox,
                const irr::core::vector3df &currentCharacterPosition) const;
            bool checkCollisionWithBombs(EntityManager &entityManager, const irr::core::aabbox3df &characterBoundingBox, int characterId) const;
            bool checkCollisionWithPowerUp(
                EntityManager &entityManager, const irr::core::aabbox3df &characterBoundingBox, Components::POWERUP_TYPE type) const;
            void checkCollisionWithPowerUps(
                EntityManager &entityManager, const irr::core::aabbox3df &characterBoundingBox, Components::PlayerComponent *playerComponent) const;
            irr::core::aabbox3df updateCharacterBoundingBox(
                irr::core::aabbox3df characterBoundingBox, const irr::core::vector3df &currentPosition, const irr::core::vector3df &wantedPosition) const;
    };
} // namespace Indie::Systems

#endif /* !COLLISIONSYSTEM_HPP_ */
