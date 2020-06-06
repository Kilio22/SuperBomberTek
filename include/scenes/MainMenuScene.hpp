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
#include <unordered_map>
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
        enum class BUTTON_TYPE
        {
            SOLO,
            MULTI,
            OPTIONS,
            CREDITS,
            QUITTER,
            NONE
        };

        ContextManager &context;
        UiSelector selector;
        std::unordered_map<BUTTON_TYPE, std::unique_ptr<Button>> buttons;
        Image *title;
        Image *bomb;
    };
}

#endif /* !MAINMENUSCENE_HPP_ */