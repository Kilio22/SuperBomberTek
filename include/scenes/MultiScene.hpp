/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** MultiScene
*/

#ifndef MULTI1SCENE_HPP_
#define MULTI1SCENE_HPP_

#include "Checkbox.hpp"
#include "ContextManager.hpp"
#include "IScene.hpp"
#include "UiSelector.hpp"
#include "Bar.hpp"
#include <memory>
#include <unordered_map>
#include <vector>

namespace Indie
{
    struct InitGame;
    class MultiScene : public IScene
    {
    public:
        MultiScene(ContextManager &context);
        ~MultiScene() = default;

        void init() final;
        void reset() final;
        void update(irr::f32 deltaTime) final;
        void renderPre3D() final;
        void renderPost3D() final;

    private:
        void skipScene(bool update, bool render, bool subUpdate, bool subRender);
        irr::scene::IAnimatedMeshSceneNode *createTheme(const std::string &filepath);

    private:
        enum class BUTTON_TYPE
        {
            THEME,
            MAP,
            AI,
            TIME,
            PLAY,
            BACK,
            NONE
        };

        enum class UI_SELECTOR_TYPE
        {
            DEFAULT,
            THEME,
            MAP,
            AI,
            TIME,
            NONE
        };

        static const std::unordered_map<UI_SELECTOR_TYPE, irr::core::vector2di> uiSelectorsSize;

        ContextManager &context;
        std::unordered_map<UI_SELECTOR_TYPE, std::unique_ptr<UiSelector>> uiSelectors;
        std::unordered_map<BUTTON_TYPE, std::unique_ptr<Button>> buttons;
        std::unique_ptr<Checkbox> pUps;
        Image *title;
        Image *layout;
        Image *whiteBg;
        Bar xpBar;
        irr::gui::IGUIFont *font;
        // Faut pas oublier de clear le scenemanager
        irr::scene::IAnimatedMeshSceneNode *theme1;
        irr::scene::IAnimatedMeshSceneNode *theme2;
        float modelRotation;
        std::vector<std::string> availableMaps;
        std::unique_ptr<InitGame> initGame;
        unsigned short int xp;
        unsigned short int lvl;
    };
}

#endif /* !MULTI1SCENE_HPP_ */
