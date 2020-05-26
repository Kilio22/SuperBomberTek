/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** MainMenuScene
*/

#ifndef MAINMENUSCENE_HPP_
#define MAINMENUSCENE_HPP_

#include "IScene.hpp"
#include "UiSelector.hpp"
#include "ContextManager.hpp"
#include "Button.hpp"
#include <vector>

namespace Indie {
    class MainMenuScene : public IScene {
        public:
            MainMenuScene(ContextManager &context);
            ~MainMenuScene();

            void init();
            void reset();
            void update(irr::f32 deltaTime);
            void renderPre3D();
            void renderPost3D();

        private:
            ContextManager &context;
            UiSelector selector;
            std::unique_ptr<Button> play;
            std::unique_ptr<Button> options;
    };
}

#endif /* !MAINMENUSCENE_HPP_ */