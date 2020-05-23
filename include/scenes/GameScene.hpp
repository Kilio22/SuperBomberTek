/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** GameScene
*/

#ifndef GAMESCENE_HPP_
#define GAMESCENE_HPP_

#include "ContextManager.hpp"
#include "SystemManager.hpp"
#include "IScene.hpp"
#include "Systems.h"

namespace Indie {

    class GameScene : public IScene {
        public:
            GameScene(ContextManager &context);
            ~GameScene() = default;

            void init();
            void reset();
            void update(irr::f32 deltaTime);
            void renderPre3D();
            void renderPost3D();

        private:
            ContextManager &context;
            irr::IrrlichtDevice *device;
            irr::video::IVideoDriver *driver;
            irr::scene::ISceneManager *sceneManager;
            Indie::EntityManager &entityManager;
            Indie::SystemManager &systemManager;
    };
}

#endif /* !GAMESCENE_HPP_ */
