/*
** EPITECH PROJECT, 2020
** joujou_cmake
** File description:
** main
*/

#include <irrlicht.h>
#include <SFML/Audio.hpp>
#include <iostream>

using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

#ifdef _IRR_WINDOWS_
#pragma comment(lib, "Irrlicht.lib")
#pragma comment(linker, "/subsystem:windows /ENTRY:mainCRTStartup")
#endif

int main(void)
{
    irr::IrrlichtDevice *device = irr::createDevice(irr::video::EDT_OPENGL, irr::core::dimension2d<irr::u32>(1280, 720), 32); // On créer le device (la fenêtre en gros)
    irr::video::IVideoDriver *driver = device->getVideoDriver(); // On récupère le driver
    irr::scene::ISceneManager *sceneManager = device->getSceneManager(); // On récupère le scène manager
    irr::gui::IGUIEnvironment *gui = device->getGUIEnvironment(); // récupération du gui

    // Un peu de son
    sf::SoundBuffer buffer;
    sf::Sound sound;

    buffer.loadFromFile("../src/example.ogg");
    sound.setBuffer(buffer);
    sound.setLoop(true);
    sound.play();
    device->getCursorControl()->setVisible(false);

    // On créer une mesh (un maillage, ce qui permet de render une forme) animée
    irr::scene::IAnimatedMeshSceneNode *sydney = sceneManager->addAnimatedMeshSceneNode(sceneManager->getMesh("../ressources/sydney.md2"), 0, -1, irr::core::vector3df(-100, 45, 0));
    sydney->setMaterialFlag(irr::video::EMF_LIGHTING, false);
    sydney->setMaterialTexture(0, driver->getTexture("../ressources/sydney.bmp")); // on set la texture du mesh
    sydney->setMD2Animation(irr::scene::EMAT_STAND); // On lui dit de se mettre en position STAND

    // Creation de la map
	scene::IMetaTriangleSelector *metaSelector = sceneManager->createMetaTriangleSelector();
    std::vector<irr::scene::IAnimatedMeshSceneNode *> walls;
    irr::scene::ITriangleSelector *selector;
    irr::f32 x = 0;
    irr::f32 y = 0;

    for (size_t i = 0; i < 10; i++) {
        for (size_t j = 0; j < 10; j++) {
            irr::scene::IAnimatedMeshSceneNode *newWall = sceneManager->addAnimatedMeshSceneNode(sceneManager->getMesh("../ressources/wall.obj"), 0, -1, irr::core::vector3df(x, 0, y));
            newWall->setMaterialFlag(irr::video::EMF_LIGHTING, false);
            newWall->setMaterialTexture(0, driver->getTexture("../ressources/wall.png")); // on set la texture du mesh
            selector = sceneManager->createTriangleSelector(newWall); // On créer un selector, c'est ce qui permet de faire des collisions entre cet objet et un autre (à savoir notre perso)
            newWall->setTriangleSelector(selector); // On attribut le selector au mesh parce que c'est pas fait automatiquement c de la merde
            metaSelector->addTriangleSelector(selector); // On ajoute ce selector dans un meta selector (un vector de selector en gros)
            selector->drop();
            walls.push_back(newWall);
            x += 20;
        }
        x = 0;
        y += 20;
    }

    // On ajoute deux murs l'un au dessus de l'autre
    irr::scene::IAnimatedMeshSceneNode *newWall = sceneManager->addAnimatedMeshSceneNode(sceneManager->getMesh("../ressources/wall.obj"), 0, -1, irr::core::vector3df(60, 20, 0));
    newWall->setMaterialFlag(irr::video::EMF_LIGHTING, false);
    newWall->setMaterialTexture(0, driver->getTexture("../ressources/wall.png")); // on set la texture
    selector = sceneManager->createTriangleSelector(newWall);
    newWall->setTriangleSelector(selector);
    metaSelector->addTriangleSelector(selector);
    selector->drop();
    walls.push_back(newWall);

    newWall = sceneManager->addAnimatedMeshSceneNode(sceneManager->getMesh("../ressources/wall.obj"), 0, -1, irr::core::vector3df(60, 40, 0));
    newWall->setMaterialFlag(irr::video::EMF_LIGHTING, false);
    newWall->setVisible(false);
    selector = sceneManager->createTriangleSelector(newWall);
    newWall->setTriangleSelector(selector);
    metaSelector->addTriangleSelector(selector);
    selector->drop();
    walls.push_back(newWall);

    // Faire aller d'un point à un autre (pour que ca fonctionne avec la collision faut mettre cette animation avant celle de la collision)
    const vector3df initPosition = sydney->getAbsolutePosition();
    const vector3df destPosition(2000, 0, 0);
    scene::ISceneNodeAnimator *anim = sceneManager->createFlyStraightAnimator(initPosition, destPosition, 50000); // Elle va courir jusqu'en 2000 0 0

    // on créer le système de collision à partir du metaSelector dans lequel on a mit les selector de tout les cubes
    sydney->addAnimator(anim); // On ajoute l'animation
    const core::aabbox3d<f32> &box = sydney->getBoundingBox();
    core::vector3df radius = box.MaxEdge - box.getCenter();
    anim = sceneManager->createCollisionResponseAnimator(metaSelector, sydney, radius, core::vector3df(0, 0,0));
    sydney->addAnimator(anim);
    anim->drop();

    // Controler la camera avec les touches
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

    /* RENDU */
    wchar_t text[100] = {'\0'};
    irr::gui::IGUIStaticText *guiText = gui->addStaticText(text, irr::core::rect<irr::s32>(10, 10, 50, 20), true);
    swprintf(text, 100, L"FPS: %d", driver->getFPS());
    while (device->run()) {
        driver->beginScene(true, true, irr::video::SColor(0,255,255,255));
        swprintf(text, 100, L"FPS: %d", driver->getFPS());
        guiText->setText(text);
        sceneManager->drawAll();
        gui->drawAll();
        driver->endScene();
        memset(text, '\0', 100);
    }
    device->drop ();
    return 0;
}