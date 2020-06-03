/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** SoloScene
*/

#ifndef SOLOSCENE_HPP_
#define SOLOSCENE_HPP_

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

    private:
        ContextManager &context;
        UiSelector selector;
        UiSelector charaSelector;
        UiSelector themeSelector;
        UiSelector mapSelector;
        std::unique_ptr<Button> charaButton;
        std::unique_ptr<Button> themeButton;
        std::unique_ptr<Button> mapButton;
        std::unique_ptr<Button> play;
        std::unique_ptr<Button> back;
        std::unique_ptr<Checkbox> pUps;
        Image *title;
        Image *layout;
        Image *kbLayout;
        irr::gui::IGUIFont *font;
        std::unique_ptr<Keybind> up;
        std::unique_ptr<Keybind> down;
        std::unique_ptr<Keybind> left;
        std::unique_ptr<Keybind> right;
        std::unique_ptr<Keybind> bomb;
        irr::scene::IAnimatedMeshSceneNode *theme1;
        irr::scene::IAnimatedMeshSceneNode *theme2;
        static const std::vector<std::pair<std::string, Components::PlayerComponent::PLAYER_COLOR>> charaPaths;
        static const std::vector<std::string> mapPaths;
        // PARAMS (psk inclusion circulaire à cause du include GameScene.hpp dans InitGame.hpp)
        char mode;
        char nbAi;
        Components::THEME mapTheme;
        Components::MAP_TYPE mapType;
        bool powerUp;
        std::string mapPath;
        time_t timeLimit;
        std::string playerTexture;
        std::vector<std::pair<irr::EKEY_CODE, Indie::Components::KEY_TYPE>> playerKeys;
        std::vector<irr::EKEY_CODE> playerKeyCodes;
        Components::PlayerComponent::PLAYER_COLOR playerColor;
        // TODO : XP BAR
        // TODO : SCORE
        // TODO : Recup le level et l'xp qqpart. Faudra just set les valeurs du coup.
        unsigned short int xp;
        unsigned short int lvl;
    };
}

#endif /* !SOLOSCENE_HPP_ */
