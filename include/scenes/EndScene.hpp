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
#include "EndGameInfo.hpp"
#include "IScene.hpp"
#include "UiSelector.hpp"
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

            Indie::EndGame *getEndGame(void) const;
            void setEndGame(const Indie::EndGame &endGame);

        private:
            ContextManager &context;
            UiSelector selector;
            std::unique_ptr<Button> menu;
            std::unique_ptr<Button> restart;
            Image *title;
            irr::gui::IGUIFont *font;
            std::unique_ptr<Indie::EndGame> endGame;
    };
}

#endif /* !ENDSCENE_HPP_ */