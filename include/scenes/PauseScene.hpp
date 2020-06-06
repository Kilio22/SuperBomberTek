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
#include <unordered_map>

namespace Indie
{
    class PauseScene : public IScene
    {
        public:
        enum class PAUSE_ASSETS { CONTINUE, MENU, QUIT, RESTART, BOMBER, TITLE, BG };

        PauseScene(ContextManager &context);
        ~PauseScene();

        void init() final;
        void reset() final;
        void update(irr::f32 deltaTime) final;
        void renderPre3D() final;
        void renderPost3D() final;

        private:
        enum class BUTTON_TYPE {
            PLAY,
            MENU,
            RESTART,
            QUIT,
            NONE
        };

        ContextManager &context;
        UiSelector selector;
        Image *bg;
        Image *bomber;
        Image *title;
        std::unordered_map<BUTTON_TYPE, std::unique_ptr<Button>> buttons;

        static const std::unordered_map<PAUSE_ASSETS, std::string> assets_paths;
    };
}

#endif /* !PAUSESUBSCENE_HPP_ */
