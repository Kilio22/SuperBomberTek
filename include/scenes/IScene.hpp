/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** IScene
*/

#ifndef ISCENE_HPP_
#define ISCENE_HPP_

#include "ContextManager.hpp"

namespace Indie
{
    class IScene {
        public:
            virtual ~IScene() = default;

            virtual void init() = 0;
            virtual void reset() = 0;
            virtual void update(irr::f32 deltaTime) = 0;
            virtual void renderPre3D() = 0;
            virtual void renderPost3D() = 0;
    };
}

#endif /* !ISCENE_HPP_ */
