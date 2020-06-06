/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** MultiKeybindsScene
*/

#ifndef MULTIKEYBINDSSCENE_HPP_
#define MULTIKEYBINDSSCENE_HPP_

#include "InputComponent.hpp"
#include "ContextManager.hpp"
#include "IScene.hpp"
#include "Keybind.hpp"
#include "UiSelector.hpp"
#include "SceneManager.hpp"
#include <memory>
#include <vector>

namespace Indie
{
    struct InitGame;

    class MultiKeybindsScene : public IScene
    {
    public:
        MultiKeybindsScene(ContextManager &context);
        ~MultiKeybindsScene() = default;

        void init() final;
        void reset() final;
        void update(irr::f32 deltaTime) final;
        void renderPre3D() final;
        void renderPost3D() final;
        void setData(InitGame *initGame);

    private:
        void skipScene(bool update, bool render, bool subUpdate, bool subRender);
        void initGameStruct(SceneManager &manager);
        std::string getFileName(std::string const &filepath);

    private:
        /* ========== OTHER ========== */
        ContextManager &context;
        UiSelector selector;
        UiSelector p1CharaSelector;
        UiSelector p2CharaSelector;
        std::unique_ptr<Button> play;
        std::unique_ptr<Button> back;
        Image *title;
        Image *layout;
        irr::gui::IGUIFont *font;
        std::vector<std::pair<Indie::Components::KEY_TYPE, std::shared_ptr<Keybind>>> pKeybinds;
        /* ========== P1 ========== */
        std::unique_ptr<Button> p1CharaButton;
        std::vector<std::pair<Indie::Components::KEY_TYPE, std::shared_ptr<Keybind>>> p1Keybinds;
        /* ========== P2 ========== */
        std::unique_ptr<Button> p2CharaButton;
        std::vector<std::pair<Indie::Components::KEY_TYPE, std::shared_ptr<Keybind>>> p2Keybinds;
        /* ========== FROM MULTI1 ========== */
        std::unique_ptr<InitGame> initGame;
    };
}

#endif /* !MULTIKEYBINDSSCENE_HPP_ */