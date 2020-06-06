/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** RenderSystem
*/

#ifndef RENDERSYSTEM_HPP_
#define RENDERSYSTEM_HPP_

#include "ISystem.hpp"
#include "MapComponent.hpp"

namespace Indie::Systems
{
    class RenderSystem : public ISystem
    {
        public:
            RenderSystem() = default;
            ~RenderSystem() = default;

            void onUpdate(irr::f32 deltaTime, EntityManager &entityManager) const final;

        private:
            void checkMapState(EntityManager &entityManager) const;
            void changeBoxes(EntityManager &entityManager, Components::MAP_STATE state) const;
            void changeBox(Entity *wall, Components::MAP_STATE state) const;
    };
}

#endif /* !RENDERSYSTEM_HPP_ */
