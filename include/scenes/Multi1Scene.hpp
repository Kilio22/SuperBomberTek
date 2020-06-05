/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** Multi1Scene
*/

#ifndef MULTI1SCENE_HPP_
#define MULTI1SCENE_HPP_

#include "Checkbox.hpp"
#include "ContextManager.hpp"
#include "IScene.hpp"
#include "UiSelector.hpp"
#include "Components.h"
#include <memory>
#include <vector>
#include <utility>

namespace Indie
{
    class Multi1Scene : public IScene
    {
    public:
        Multi1Scene(ContextManager &context);
        ~Multi1Scene();

        void init() final;
        void reset() final;
        void update(irr::f32 deltaTime) final;
        void renderPre3D() final;
        void renderPost3D() final;
        //void setData(char nbAi, Components::THEME mapTheme, Components::MAP_TYPE mapType, bool powerUp, std::string mapPath, time_t timeLimit, int nbAi);

    private:
        void skipScene(bool update, bool render, bool subUpdate, bool subRender);

    private:
        ContextManager &context;
        UiSelector selector;
        UiSelector themeSelector;
        UiSelector mapSelector;
        UiSelector iaSelector;
        UiSelector timeSelector;
        std::unique_ptr<Button> themeButton;
        std::unique_ptr<Button> mapButton;
        std::unique_ptr<Button> iaButton;
        std::unique_ptr<Button> timeButton;
        std::unique_ptr<Button> play;
        std::unique_ptr<Button> back;
        std::unique_ptr<Checkbox> pUps;
        bool pUpsEnabled;
        Image *title;
        Image *layout;
        Image *whiteBg;
        irr::gui::IGUIFont *font;
        // Faut pas oublier de clear le scenemanager
        irr::scene::ICameraSceneNode *camera;
        irr::scene::IAnimatedMeshSceneNode *theme1;
        irr::scene::IAnimatedMeshSceneNode *theme2;
        float modelRotation;
        std::vector<std::string> mapPaths;
        // PARAMS (Faudra les filer à multi 2 avec une fonction publique de multi 2)
        int nbAi;
        Components::THEME mapTheme;
        Components::MAP_TYPE mapType;
        bool powerUp;
        std::string mapPath;
        time_t timeLimit;
        // TODO : XP BAR
        // TODO : SCORE
        // TODO : Recup le level et l'xp qqpart. Faudra just set les valeurs du coup.
        unsigned short int xp;
        unsigned short int lvl;
    };
}

#endif /* !MULTI1SCENE_HPP_ */
