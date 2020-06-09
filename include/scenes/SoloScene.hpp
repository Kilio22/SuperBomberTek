/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** SoloScene
*/

#ifndef SOLOSCENE_HPP_
#define SOLOSCENE_HPP_

#include "Checkbox.hpp"
#include "IScene.hpp"
#include "InputComponent.hpp"
#include "Keybind.hpp"
#include "PlayerSkins.hpp"
#include "SceneManager.hpp"
#include "UiSelector.hpp"
#include "Bar.hpp"
#include <memory>
#include <vector>

namespace Indie
{
    struct InitGame;
    struct PlayerParams;

    class SoloScene : public IScene
    {
    public:
        SoloScene(ContextManager &context);
        ~SoloScene() = default;

        void init() final;
        void reset() final;
        void update(irr::f32 deltaTime) final;
        void renderPre3D() final;
        void renderPost3D() final;
        void setKeybinds(const std::vector<std::pair<Indie::Components::KEY_TYPE, std::unique_ptr<Keybind>>> &keybinds);
        const std::vector<std::pair<Indie::Components::KEY_TYPE, std::unique_ptr<Keybind>>> &getKeybinds(void) const;
        void resetKeybinds(void);
        std::string getFileName(std::string const &filepath);

    private:
        enum class BUTTON_TYPE
        {
            SKIN,
            THEME,
            MAP,
            PLAY,
            BACK,
            NONE
        };

        enum class UI_SELECTOR_TYPE
        {
            DEFAULT,
            SKIN,
            THEME,
            MAP,
            NONE
        };

        static const std::unordered_map<UI_SELECTOR_TYPE, irr::core::vector2di> uiSelectorsSize;

        void skipScene(bool update, bool render, bool subUpdate, bool subRender);
        irr::scene::IAnimatedMeshSceneNode *createTheme(const std::string &filepath);
        void initGameStruct(SceneManager &sceneManager);

        ContextManager &context;
        std::unordered_map<SoloScene::UI_SELECTOR_TYPE, std::unique_ptr<UiSelector>> uiSelectors;
        std::unordered_map<SoloScene::BUTTON_TYPE, std::unique_ptr<Button>> buttons;
        std::vector<std::pair<Indie::Components::KEY_TYPE, std::unique_ptr<Keybind>>> keybinds;
        std::unique_ptr<Checkbox> pUps;
        Bar xpBar;
        Image *title;
        Image *layout;
        Image *kbLayout;
        irr::gui::IGUIFont *font;
        irr::scene::IAnimatedMeshSceneNode *theme1;
        irr::scene::IAnimatedMeshSceneNode *theme2;
        irr::scene::IAnimatedMeshSceneNode *theme3;
        float modelRotation;
        std::vector<std::string> availableMaps;
        std::vector<std::pair<std::string, Components::PlayerComponent::PLAYER_COLOR>> availableSkins;
        std::unique_ptr<InitGame> initGame;
        std::unique_ptr<PlayerParams> playerParams;
        unsigned int lvl;
    };
}

#endif /* !SOLOSCENE_HPP_ */
