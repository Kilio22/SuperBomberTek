/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** MeshSystem
*/

#ifndef MESHSYSTEM_HPP_
#define MESHSYSTEM_HPP_

#include "ISystem.hpp"
#include "RenderComponent.hpp"

namespace Indie::Systems
{
    class MeshSystem : public ISystem
    {
        public:
            MeshSystem() = default;
            ~MeshSystem() = default;

            void onUpdate(irr::f32 deltaTime, EntityManager &entityManager) const final;

        protected:
        private:
            void changeMesh(const ContextManager &contextManager, Indie::Components::RenderComponent *renderComp, irr::scene::IAnimatedMesh *mesh, irr::video::ITexture *texture) const;
    };
}

#endif /* !MESHSYSTEM_HPP_ */
