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

            void onUpdate(int ticks, EntityManager &) const final;

        protected:
        private:
            void changeMesh(Indie::Components::RenderComponent *, const std::string &, const std::string &) const;
    };
}

#endif /* !MESHSYSTEM_HPP_ */
