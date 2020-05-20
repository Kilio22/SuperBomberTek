/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** main
*/

#include <irrlicht.h>
#include <iostream>
#include "EntityManager.hpp"
#include "RenderSystem.hpp"
#include "MusicManager.hpp"
#include "ContextManager.hpp"
#include "MapGenerator.hpp"

int main(void)
{
    MusicManager::AddMusic("../ressources/musics/main_menu.wav"); // id 0
    MusicManager::AddMusic("../ressources/musics/level_select.wav"); // id 1
    MusicManager::setVolume(1);
    MusicManager::setMusic(1);
    MusicManager::playMusic();

    ContextManager contextManager(irr::core::dimension2d<irr::u32>(1280, 720));

    irr::IrrlichtDevice *device = contextManager.getDevice();
    irr::video::IVideoDriver *driver = contextManager.getDriver();
    irr::scene::ISceneManager *sceneManager = contextManager.getSceneManager();

    Indie::EntityManager entityManager;
    Indie::Systems::RenderSystem renderSystem;
    irr::SKeyMap keyMap[4];                             // re-assigne les commandes
    keyMap[0].Action = irr::EKA_MOVE_FORWARD;           // avancer
    keyMap[0].KeyCode = irr::KEY_KEY_Z;
    keyMap[1].Action = irr::EKA_MOVE_BACKWARD;          // reculer
    keyMap[1].KeyCode = irr::KEY_KEY_S;
    keyMap[2].Action = irr::EKA_STRAFE_LEFT;            // a gauche
    keyMap[2].KeyCode = irr::KEY_KEY_Q;
    keyMap[3].Action = irr::EKA_STRAFE_RIGHT;           // a droite
    keyMap[3].KeyCode = irr::KEY_KEY_D;

    irr::scene::ICameraSceneNode *camera = sceneManager->addCameraSceneNodeFPS(0, 100.0f, 0.1f, -1, keyMap, 4);
    camera->setPosition(irr::core::vector3df(irr::f32(140), irr::f32(200), irr::f32(-30)));
    camera->setTarget(irr::core::vector3df(irr::f32(140), irr::f32(0), irr::f32(150)));

    irr::f32 x = 0;
    irr::f32 y = 0;

    // Lumière et brouillard quand on s'éloigne
    driver->setFog(irr::video::SColor(10, 0, 0, 0), irr::video::EFT_FOG_LINEAR, 200.0f, 800.0f, 0.005f, true, true);
    sceneManager->setAmbientLight (irr::video::SColorf(0.5,0.5,0.5,0.5));
    //J'ai foutu la camera en parent, du coup ça éclaire autours de la cam.
    sceneManager->addLightSceneNode (camera, irr::core::vector3df(0, 0, 0), irr::video::SColorf(1.0f, 1.0f, 1.0f, 0.0f), 500.0f);

    for (size_t i = 0; i < 15; i++) {
        for (size_t j = 0; j < 15; j++) {
            entityManager.createGround(irr::core::vector3df(x, 0, y), "../ressources/static_mesh/map_dirt/ground.obj", "../ressources/static_mesh/map_dirt/ground.png", contextManager);
            x += 20;
        }
        x = 0;
        y += 20;
    }
    
    Indie::MapGenerator generator(Indie::MapGenerator::DEFAULT);

    std::vector<std::vector<int>> map = generator.getMap();
    for (size_t i = 0; i < 15; i++) {
        for (size_t j = 0; j < 15; j++) {
            if (map[i][j] == -1)
                entityManager.createGround(irr::core::vector3df(20 * i, 20, 20 * j), "../ressources/static_mesh/map_dirt/wall_side.obj", "../ressources/static_mesh/map_dirt/wall_side.png", contextManager);
            else if (map[i][j] == 1)
                entityManager.createGround(irr::core::vector3df(20 * i, 20, 20 * j), "../ressources/static_mesh/map_dirt/box.obj", "../ressources/static_mesh/map_dirt/box.png", contextManager);
            else if (map[i][j] == 2)
                entityManager.createGround(irr::core::vector3df(20 * i, 20, 20 * j), "../ressources/static_mesh/map_dirt/wall_middle.obj", "../ressources/static_mesh/map_dirt/wall_middle.png", contextManager);
            else if (map[i][j] == 3)
                entityManager.createGround(irr::core::vector3df(20 * i, 20, 20 * j), "../ressources/static_mesh/map_stone/ground.obj", "../ressources/static_mesh/map_stone/ground.png", contextManager);
        }
    }

    device->getCursorControl()->setVisible(false);
    while (device->run()) {
        MusicManager::update();
        driver->beginScene(true, true, irr::video::SColor(0,0,0,0));
        renderSystem.onUpdate(0, entityManager);
        sceneManager->drawAll();
        driver->endScene();
    }
    return 0;
}