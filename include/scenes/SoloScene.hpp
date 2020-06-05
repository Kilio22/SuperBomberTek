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

    public:
        static const std::vector<std::pair<std::string, Components::PlayerComponent::PLAYER_COLOR>> charaPaths;

    private:
        void resetKeybinds(void);
        void getSavedKeybinds(void);

        enum class BUTTON_TYPE
        {
            SKIN,
            THEME,
            MAP,
            PLAY,
            BACK,
            NONE
        };

        ContextManager &context;
        UiSelector selector;
        UiSelector charaSelector;
        UiSelector themeSelector;
        UiSelector mapSelector;
        std::map<SoloScene::BUTTON_TYPE, std::unique_ptr<Button>> buttons;
        std::unique_ptr<Checkbox> pUps;
        bool pUpsEnabled;
        Image *title;
        Image *layout;
        Image *kbLayout;
        irr::gui::IGUIFont *font;
        std::vector<std::pair<Indie::Components::KEY_TYPE, std::unique_ptr<Keybind>>> keybinds;
        irr::scene::ICameraSceneNode *camera;
        irr::scene::IAnimatedMeshSceneNode *theme1;
        irr::scene::IAnimatedMeshSceneNode *theme2;
        float modelRotation;
        std::vector<std::string> mapPaths;
        // PARAMS (psk inclusion circulaire à cause du include GameScene.hpp dans InitGame.hpp)
        char nbAi;
        Components::THEME mapTheme;
        Components::MAP_TYPE mapType;
        bool powerUp;
        std::string mapPath;
        time_t timeLimit;
        std::string playerTexture;
        std::vector<std::pair<irr::EKEY_CODE, Indie::Components::KEY_TYPE>> playerKeys;
        Components::PlayerComponent::PLAYER_COLOR playerColor;
        // TODO : XP BAR
        // TODO : SCORE
        // TODO : Recup le level et l'xp qqpart. Faudra just set les valeurs du coup.
        unsigned short int xp;
        unsigned short int lvl;
    };
}

#endif /* !SOLOSCENE_HPP_ */
