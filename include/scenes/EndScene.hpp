/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** EndScene
*/

#ifndef ENDSCENE_HPP_
#define ENDSCENE_HPP_

#include "Button.hpp"
#include "ContextManager.hpp"
#include "IScene.hpp"
#include "UiSelector.hpp"
#include "MasterInfo.hpp"
#include "EndGameInfo.hpp"
#include <string>
#include <memory>

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

            void skipScene(bool update, bool render, bool subUpdate, bool subRender);

            const Indie::EndGame &getEndGame(void) const;
            void setEndGame(const Indie::EndGame &endGame);

            void increaseXp(Indie::MasterInfo *info);

        private:
            ContextManager &context;
            UiSelector selector;
            std::unique_ptr<Button> menu;
            std::unique_ptr<Button> restart;
            Image *title;
            irr::gui::IGUIFont *font;
            EndGame endGame;

            float nbXpToSub = 0;
            float xpToAdd = 0;
    };
}

#endif /* !ENDSCENE_HPP_ */
