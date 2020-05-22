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

            void onUpdate(int ticks, EntityManager &entityManager, const ContextManager &contextManager) const final;

        protected:
        private:
            void changeMesh(const ContextManager &contextManager, Indie::Components::RenderComponent *renderComponent, const std::string &meshPath, const std::string &texturePath) const;
    };
}

#endif /* !MESHSYSTEM_HPP_ */
