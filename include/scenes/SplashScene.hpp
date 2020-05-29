/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** SplashScene
*/

#ifndef SPLASHSCENE_HPP_
#define SPLASHSCENE_HPP_

#include "ContextManager.hpp"
#include "EventHandler.hpp"
#include "IScene.hpp"
#include "Parallax.hpp"
#include "ServiceLocator.hpp"
#include <vector>

namespace Indie
{
    class SplashScene : public IScene
    {
        public:
        SplashScene(ContextManager &context);
        ~SplashScene() = default;

        void init() final;
        void reset() final;
        void update(irr::f32 deltaTime) final;
        void renderPre3D() final;
        void renderPost3D() final;

        private:
        ContextManager &context;
        Image *background;
    };
}

#endif /* !SPLASHSCENE_HPP_ */