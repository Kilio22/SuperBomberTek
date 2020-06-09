/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** SaveScene
*/

#ifndef SAVESCENE_HPP_
#define SAVESCENE_HPP_

#include "Button.hpp"
#include "ContextManager.hpp"
#include "IScene.hpp"
#include "Prompt.hpp"
#include "UiSelector.hpp"
#include <memory>
#include <unordered_map>

namespace Indie
{
    class SaveScene : public IScene
    {
        public:
            SaveScene(ContextManager &context);
            ~SaveScene() = default;

            void init() final;
            void reset() final;
            void update(irr::f32 deltaTime) final;
            void renderPre3D() final;
            void renderPost3D() final;
            void skipScene(bool update, bool render, bool subUpdate, bool subRender);

        private:
            void onUpdate();

            enum class SAVE_BUTTON_TYPE
            {
                SAVE1,
                SAVE2,
                SAVE3,
                NONE
            };

            ContextManager &context;
            UiSelector selector;
            std::unordered_map<SAVE_BUTTON_TYPE, std::unique_ptr<Button>> saveButtons;
            std::unique_ptr<Button> play;
            std::unique_ptr<Prompt> prompt;
            Image *title;
            irr::gui::IGUIFont *font;
            int saveSelected;
            std::vector<std::pair<std::string, time_t>> savedGame;
    };
}

#endif /* !SAVESCENE_HPP_ */
