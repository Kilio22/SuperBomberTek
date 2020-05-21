/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** GameScene
*/

#ifndef GAMESCENE_HPP_
#define GAMESCENE_HPP_

#include <iostream>

#include "IScene.hpp"
#include "Parallax.hpp"
#include "ContextManager.hpp"

#include "Components.h"
#include "EntityBuilder.h"
#include "EntityManager.hpp"
#include "MapGenerator.hpp"
#include "Systems.h"

class GameScene : public IScene {
    public:
        GameScene() {}
        ~GameScene() {}

        bool init(ContextManager &context);
        bool reset(ContextManager &context);
        void update();
        void renderPre3D();
        void renderPost3D();

    private:
        ContextManager *context;
        irr::IrrlichtDevice *device;
        irr::video::IVideoDriver *driver;
        irr::scene::ISceneManager *sceneManager;
        Indie::EntityManager entityManager;
        Indie::Systems::RenderSystem renderSystem;
        Indie::Systems::InputSystem inputSystem;
        Indie::Systems::MoveSystem moveSystem;
        Indie::Systems::RotationSystem rotationSystem;
        Indie::Systems::VelocitySystem velocitySystem;
        Indie::Systems::MeshSystem meshSystem;
        Indie::Systems::CollisionSystem collisionSystem;
};

#endif /* !GAMESCENE_HPP_ */
