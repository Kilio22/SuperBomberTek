/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** MainMenuScene
*/

#ifndef MAINMENUSCENE_HPP_
#define MAINMENUSCENE_HPP_

#include "Button.hpp"
#include "ContextManager.hpp"
#include "IScene.hpp"
#include "UiSelector.hpp"
#include <memory>
#include <vector>

namespace Indie
{
    class MainMenuScene : public IScene
    {
        public:
        MainMenuScene(ContextManager &context);
        ~MainMenuScene();

        void init() final;
        void reset() final;
        void update(irr::f32 deltaTime) final;
        void renderPre3D() final;
        void renderPost3D() final;
        void skipScene(bool update, bool render, bool subUpdate, bool subRender);

        private:
        ContextManager &context;
        UiSelector selector;
        std::unique_ptr<Button> solo;
        std::unique_ptr<Button> multi;
        std::unique_ptr<Button> options;
        std::unique_ptr<Button> credits;
        std::unique_ptr<Button> quitter;
        Image *title;
        Image *bomb;
    };
}

#endif /* !MAINMENUSCENE_HPP_ */