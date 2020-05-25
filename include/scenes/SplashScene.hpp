/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** SplashScene
*/

#ifndef SPLASHSCENE_HPP_
#define SPLASHSCENE_HPP_

#include "IScene.hpp"
#include "Parallax.hpp"
#include "ContextManager.hpp"
#include "ServiceLocator.hpp"
#include "EventHandler.hpp"
#include <vector>

namespace Indie {
    class SplashScene : public IScene {
        public:
            SplashScene(ContextManager &context);
            ~SplashScene() = default;

            void init();
            void reset();
            void update(irr::f32 deltaTime);
            void renderPre3D();
            void renderPost3D();

        private:
            ContextManager &context;
            Image *background;
    };
}

#endif /* !SPLASHSCENE_HPP_ */