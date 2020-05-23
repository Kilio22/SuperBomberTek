/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** TitleScene
*/

#ifndef TITLESCENE_HPP_
#define TITLESCENE_HPP_

#include "IScene.hpp"
#include "ContextManager.hpp"

#define _USE_MATH_DEFINES
#include <math.h>
#include <cmath>

class TitleScene : public IScene {
    public:
        TitleScene() {}
        ~TitleScene() {}

        bool init(ContextManager &context);
        bool reset(ContextManager &context);
        void update(irr::f32 deltaTime);
        void renderPre3D();
        void renderPost3D();

    private:
        ContextManager *context;
        Image *titleLogo = NULL;
        Image *pressText = NULL;
        double offsetY = 0;
        double offsetAlpha = 0;
        static const double updateRate;
};

#endif /* !TITLESCENE_HPP_ */
