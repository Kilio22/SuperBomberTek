/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** Multi2Scene
*/

#ifndef MULTI2SCENE_HPP_
#define MULTI2SCENE_HPP_

#include "Checkbox.hpp"
#include "ContextManager.hpp"
#include "IScene.hpp"
#include "UiSelector.hpp"
#include "Keybind.hpp"
#include "Components.h"
#include <memory>
#include <vector>
#include <utility>

namespace Indie
{
    class Multi2Scene : public IScene
    {
    public:
        Multi2Scene(ContextManager &context);
        ~Multi2Scene();

        void init() final;
        void reset() final;
        void update(irr::f32 deltaTime) final;
        void renderPre3D() final;
        void renderPost3D() final;
        void setData(char nbAi, Components::THEME mapTheme, Components::MAP_TYPE mapType, bool powerUp, std::string mapPath, time_t timeLimit);

    private:
        void skipScene(bool update, bool render, bool subUpdate, bool subRender);

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
        std::vector<std::pair<irr::EKEY_CODE, Indie::Components::KEY_TYPE>> playerKeys;
        std::vector<std::pair<Indie::Components::KEY_TYPE, std::shared_ptr<Keybind>>> pKeybinds;
        /* ========== P1 ========== */
        std::unique_ptr<Button> p1CharaButton;
        std::vector<std::pair<Indie::Components::KEY_TYPE, std::shared_ptr<Keybind>>> p1Keybinds;
        /* ========== P2 ========== */
        std::unique_ptr<Button> p2CharaButton;
        std::vector<std::pair<Indie::Components::KEY_TYPE, std::shared_ptr<Keybind>>> p2Keybinds;
        /* ========== FROM MULTI1 ========== */
        char nbAi;
        Components::THEME mapTheme;
        Components::MAP_TYPE mapType;
        bool powerUp;
        std::string mapPath;
        time_t timeLimit;
    };
}

#endif /* !MULTI2SCENE_HPP_ */