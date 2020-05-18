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

int main(void)
{
    irr::IrrlichtDevice *device = irr::createDevice(irr::video::EDT_OPENGL, irr::core::dimension2d<irr::u32>(1280, 720), 32); // On créer le device (la fenêtre en gros)
    irr::video::IVideoDriver *driver = device->getVideoDriver(); // On récupère le driver
    irr::scene::ISceneManager *sceneManager = device->getSceneManager(); // On récupère le scène manager
    Indie::EntityManager entityManager;
    Indie::System::RenderSystem renderSystem;
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
    camera->setPosition(irr::core::vector3df(irr::f32(39.5108), irr::f32(22.277), irr::f32(-10.2412)));

    irr::f32 x = 0;
    irr::f32 y = 0;

    for (size_t i = 0; i < 10; i++) {
        for (size_t j = 0; j < 10; j++) {
            entityManager.createGround(irr::core::vector3df(x, 0, y), "../ressources/wall.obj", "../ressources/wall.png", sceneManager, driver);
            x += 20;
        }
        x = 0;
        y += 20;
    }
    device->getCursorControl()->setVisible(false);
    while (device->run()) {
        driver->beginScene(true, true, irr::video::SColor(0,255,255,255));
        renderSystem.onUpdate(0, entityManager);
        sceneManager->drawAll();
        driver->endScene();
    }
    return 0;
}