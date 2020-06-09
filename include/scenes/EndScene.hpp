/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** EndScene
*/

#ifndef ENDSCENE_HPP_
#define ENDSCENE_HPP_

#include "Button.hpp"
#include "Bar.hpp"
#include "ContextManager.hpp"
#include "IScene.hpp"
#include "UiSelector.hpp"
#include "MasterInfo.hpp"
#include "EndGameInfo.hpp"
#include <string>
#include <memory>
#include <unordered_map>

namespace Indie
{
    class EndScene : public IScene
    {
        public:
            EndScene(ContextManager &context);
            ~EndScene() = default;

            void init() final;
            void reset() final;
            void update(irr::f32 deltaTime) final;
            void renderPre3D() final;
            void renderPost3D() final;

            const Indie::EndGame &getEndGame(void) const;
            void setEndGame(const Indie::EndGame &endGame);
            void setPlayerNames(const std::vector<std::string> &names);

        private:

            enum class UI_IMAGE_TYPE
            {
                BG,
                LAYOUT,
                LVL_UP_PLAYER,
                LVL_UP_MAP,
                NONE
            };

            enum class GAME_MODE
            {
                SOLO,
                MULTI
            };

            void increaseXp(Indie::MasterInfo &info);
            void skipScene(bool update, bool render, bool subUpdate, bool subRender);

            ContextManager &context;
            UiSelector selector;
            std::unique_ptr<Button> menu;
            std::unique_ptr<Button> restart;
            time_t popUpDuration;
            Bar xpBar;
            static const std::unordered_map<UI_IMAGE_TYPE, std::string> imagePaths;
            std::unordered_map<UI_IMAGE_TYPE, Image*> images;
            std::vector<std::string> playerNames;
            irr::gui::IGUIFont *font;
            irr::gui::IGUIFont *fontBig;
            irr::gui::IGUIFont *fontVeryBig;
            EndGame endGame;
            GAME_MODE mode;
            wchar_t endText[100];
            UI_IMAGE_TYPE lvlUpType;

            float nbXpToSub = 0;
            float xpToAdd = 0;
    };
}

#endif /* !ENDSCENE_HPP_ */