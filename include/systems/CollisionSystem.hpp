/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** CollisionSystem
*/

#ifndef COLLISIONSYSTEM_HPP_
#define COLLISIONSYSTEM_HPP_

#include "ISystem.hpp"

namespace Indie::Systems
{
    class CollisionSystem : public ISystem
    {
        public:
            CollisionSystem() = default;
            ~CollisionSystem() = default;

            void onUpdate(irr::f32 deltaTime, EntityManager &entityManager) const final;

        protected:
        private:
            bool checkCollisionWithWalls(EntityManager &entityManager, const irr::core::aabbox3df &characterBoundingBox) const;
            bool checkCollisionWithCharacters(EntityManager &entityManager, const irr::core::aabbox3df &characterBoundingBox, const irr::core::vector3df &currentCharacterPosition) const;
            irr::core::aabbox3df updateCharacterBoundingBox(irr::core::aabbox3df characterBoundingBox, const irr::core::vector3df &currentPosition, const irr::core::vector3df &wantedPosition) const;
    };
} // namespace Indie::Systems


#endif /* !COLLISIONSYSTEM_HPP_ */
