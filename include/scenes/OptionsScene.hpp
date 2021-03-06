/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** OptionsScene
*/

#ifndef OPTIONSSCENE_HPP_
#define OPTIONSSCENE_HPP_

#include "Checkbox.hpp"
#include "ContextManager.hpp"
#include "IScene.hpp"
#include "UiSelector.hpp"
#include <memory>

namespace Indie
{
    class OptionsScene : public IScene
    {
    public:
        OptionsScene(ContextManager &context);
        ~OptionsScene() = default;

        void init() final;
        void reset() final;
        void update(irr::f32 deltaTime) final;
        void renderPre3D() final;
        void renderPost3D() final;

    private:
        void skipScene(bool update, bool render, bool subUpdate, bool subRender);

        ContextManager &context;
        UiSelector selector;
        UiSelector musicVolumeSelector;
        UiSelector soundVolumeSelector;
        std::unique_ptr<Button> back;
        std::unique_ptr<Button> musicVolume;
        std::unique_ptr<Button> soundVolume;
        std::unique_ptr<Checkbox> musicMute;
        std::unique_ptr<Checkbox> soundMute;
        Image *title;
        Image *wrench;
        Image *layout;
        irr::gui::IGUIFont *font;
    };
}

#endif /* !OPTIONSSCENE_HPP_ */