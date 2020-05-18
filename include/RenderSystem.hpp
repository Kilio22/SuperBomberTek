/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** RenderSystem
*/

#ifndef RENDERSYSTEM_HPP_
#define RENDERSYSTEM_HPP_

#include "ISystem.hpp"

namespace Indie::System
{
    class RenderSystem : public ISystem
    {
        public:
            RenderSystem() = default;
            ~RenderSystem() = default;

            void onUpdate(int ticks, EntityManager &) final;

        protected:
        private:
    };
}

#endif /* !RENDERSYSTEM_HPP_ */
