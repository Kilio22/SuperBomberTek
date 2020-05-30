/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** SplashScene
*/

#ifndef SPLASHSCENE_HPP_
#define SPLASHSCENE_HPP_

#include "ContextManager.hpp"
#include "EventHandler.hpp"
#include "IScene.hpp"
#include "Parallax.hpp"
#include "ServiceLocator.hpp"
#include <vector>

namespace Indie
{
    class SplashScene : public IScene
    {
        public:

        enum class SPLASH_ASSETS : int {
            BG,
            LOGO,
            PROJECT,
            BOMBER,
            END
        };

        SplashScene(ContextManager &context);
        ~SplashScene();

        void init() final;
        void reset() final;
        void update(irr::f32 deltaTime) final;
        void renderPre3D() final;
        void renderPost3D() final;

        private:
        void skipScene(void);

        ContextManager &context;
        Image *bg;
        SPLASH_ASSETS currentAsset;
        std::unordered_map<SPLASH_ASSETS, Image *> splashScreens;
        irr::u32 lastTime;

        static const std::unordered_map<SPLASH_ASSETS, std::string> splashPaths;
    };
}

#endif /* !SPLASHSCENE_HPP_ */