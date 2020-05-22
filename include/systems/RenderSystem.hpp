/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** RenderSystem
*/

#ifndef RENDERSYSTEM_HPP_
#define RENDERSYSTEM_HPP_

#include "ISystem.hpp"

namespace Indie::Systems
{
    class RenderSystem : public ISystem
    {
        public:
            RenderSystem() = default;
            ~RenderSystem() = default;

            void onUpdate(irr::f32 deltaTime, EntityManager &entityManager, const ContextManager &contextManager) const final;

        protected:
        private:
    };
}

#endif /* !RENDERSYSTEM_HPP_ */
