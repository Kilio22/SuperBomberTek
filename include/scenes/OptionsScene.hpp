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
#include <vector>

namespace Indie
{
    class OptionsScene : public IScene
    {
        public:
        OptionsScene(ContextManager &context);
        ~OptionsScene();

        void init() final;
        void reset() final;
        void update(irr::f32 deltaTime) final;
        void renderPre3D() final;
        void renderPost3D() final;
        void skipScene(bool update, bool render, bool subUpdate, bool subRender);

        private:
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
    };
}

#endif /* !OPTIONSSCENE_HPP_ */