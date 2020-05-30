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
        enum class PAUSE_ASSETS { CONTINUE, MENU, QUIT, RESTART, BOMBER, TITLE };

        PauseScene(ContextManager &context);
        ~PauseScene();

        void init() final;
        void reset() final;
        void update(irr::f32 deltaTime) final;
        void renderPre3D() final;
        void renderPost3D() final;

        private:
        ContextManager &context;
        UiSelector selector;
        Image *bomber;
        Image *title;
        std::unique_ptr<Button> play;
        std::unique_ptr<Button> menu;
        std::unique_ptr<Button> restart;
        std::unique_ptr<Button> quit;

        static const std::unordered_map<PAUSE_ASSETS, std::string> assets_paths;
    };
}

#endif /* !PAUSESUBSCENE_HPP_ */
