/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** SoloScene
*/

#ifndef SOLOSCENE_HPP_
#define SOLOSCENE_HPP_

#include "Checkbox.hpp"
#include "Components.h"
#include "ContextManager.hpp"
#include "IScene.hpp"
#include "Keybind.hpp"
#include "UiSelector.hpp"
#include <memory>
#include <utility>
#include <vector>

namespace Indie
{
    struct InitGame;
    struct PlayerParams;
    class SoloScene : public IScene
    {
    public:
        SoloScene(ContextManager &context);
        ~SoloScene();

        void init() final;
        void reset() final;
        void update(irr::f32 deltaTime) final;
        void renderPre3D() final;
        void renderPost3D() final;
        void skipScene(bool update, bool render, bool subUpdate, bool subRender);
        void setKeybinds(const std::vector<std::pair<Indie::Components::KEY_TYPE, std::unique_ptr<Keybind>>> &keybinds);
        const std::vector<std::pair<Indie::Components::KEY_TYPE, std::unique_ptr<Keybind>>> &getKeybinds(void) const;
        void resetKeybinds(void);

    public:
        static const std::vector<std::pair<std::string, Components::PlayerComponent::PLAYER_COLOR>> charaPaths;

    private:
        std::string getFileName(std::string const &filepath);
        irr::scene::IAnimatedMeshSceneNode *createTheme(const std::string &filepath);
        void initGameStruct(SceneManager &sceneManager);

        enum class BUTTON_TYPE
        {
            SKIN,
            THEME,
            MAP,
            PLAY,
            BACK,
            NONE
        };

        enum class UI_SELECTOR_TYPE {
            DEFAULT,
            SKIN,
            THEME,
            MAP,
            NONE
        };

        static const std::unordered_map<UI_SELECTOR_TYPE, irr::core::vector2di> uiSelectorsSize;

        ContextManager &context;
        std::unordered_map<SoloScene::UI_SELECTOR_TYPE, std::unique_ptr<UiSelector>> uiSelectors;
        std::unordered_map<SoloScene::BUTTON_TYPE, std::unique_ptr<Button>> buttons;
        std::unique_ptr<Checkbox> pUps;
        bool pUpsEnabled;
        Image *title;
        Image *layout;
        Image *kbLayout;
        irr::gui::IGUIFont *font;
        std::vector<std::pair<Indie::Components::KEY_TYPE, std::unique_ptr<Keybind>>> keybinds;
        irr::scene::IAnimatedMeshSceneNode *theme1;
        irr::scene::IAnimatedMeshSceneNode *theme2;
        float modelRotation;
        std::vector<std::string> mapPaths;
        // PARAMS (psk inclusion circulaire à cause du include GameScene.hpp dans InitGame.hpp)
        std::unique_ptr<InitGame> initGame;
        std::unique_ptr<PlayerParams> playerParams;
        // std::string playerTexture;
        // Components::PlayerComponent::PLAYER_COLOR playerColor;
        // TODO : XP BAR
        // TODO : Recup le level et l'xp qqpart. Faudra just set les valeurs du coup.
        unsigned short int xp;
        unsigned short int lvl;
    };
}

#endif /* !SOLOSCENE_HPP_ */
