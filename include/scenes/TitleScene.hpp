/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** TitleScene
*/

#ifndef TITLESCENE_HPP_
#define TITLESCENE_HPP_

#include "ContextManager.hpp"
#include "EventHandler.hpp"
#include "IScene.hpp"
#include "ServiceLocator.hpp"
#define _USE_MATH_DEFINES
#include <cmath>
#include <math.h>

namespace Indie
{

    class TitleScene : public IScene
    {
        public:
        TitleScene(ContextManager &context);
        ~TitleScene();

        void init() final;
        void reset() final;
        void update(irr::f32 deltaTime) final;
        void renderPre3D() final;
        void renderPost3D() final;
        void skipScene(bool update, bool render, bool subUpdate, bool subRender);

        private:
        ContextManager &context;
        Image *titleLogo = NULL;
        Image *pressText = NULL;
        double offsetY = 0;
        double offsetAlpha = 0;
        static const double updateRate;
    };
}

#endif /* !TITLESCENE_HPP_ */
