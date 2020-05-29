/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** PauseSubScene | Author: Kylian BALAN - kylian.balan@epitech.eu
*/

#ifndef PAUSESUBSCENE_HPP_
#define PAUSESUBSCENE_HPP_

#include "Button.hpp"
#include "IScene.hpp"
#include "UiSelector.hpp"
#include <memory>

namespace Indie
{
    class PauseScene : public IScene
    {
        public:
        PauseScene(ContextManager &context);
        ~PauseScene() = default;

        void init() final;
        void reset() final;
        void update(irr::f32 deltaTime) final;
        void renderPre3D() final;
        void renderPost3D() final;

        private:
        ContextManager &context;
        UiSelector selector;
        std::unique_ptr<Button> play;
        std::unique_ptr<Button> menu;
        std::unique_ptr<Button> restart;
        std::unique_ptr<Button> quit;
    };
}

#endif /* !PAUSESUBSCENE_HPP_ */
