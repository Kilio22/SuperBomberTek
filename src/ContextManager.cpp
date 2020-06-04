/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** ContextManager
*/

#include "ContextManager.hpp"
#include "MusicManager.hpp"
#include "SceneManager.hpp"
#include "driverChoice.h"

//#define DEBUG_MODE
// C'est dégueulasse avec les autre drivertype. OpenGL ftw!

Indie::ContextManager::ContextManager(irr::core::dimension2d<irr::u32> size)
{
    #ifdef DEBUG_MODE
        irr::video::E_DRIVER_TYPE driverType = irr::video::EDT_COUNT;
        while (driverType == irr::video::EDT_COUNT)
            driverType = irr::driverChoiceConsole(true);
        device = irr::createDevice(driverType, size, 32);
    
    #endif // DEBUG_MODE
    #ifndef DEBUG_MODE
        device = irr::createDevice(irr::video::EDT_OPENGL, size, 32);
    #endif // !DEBUG_MODE
    this->size = size;
    driver = device->getVideoDriver();
    sceneManager = device->getSceneManager();
    guiEnv = device->getGUIEnvironment();
}

Indie::ContextManager::~ContextManager()
{
    device->drop();
    // MusicManager::drop(); // Why
    // OUI tkt j'allais le virer
    // Ok frr
    // Ptn kylio tu del pas ça là je te vois >:c
    // mdrr c'est encore là
}

void Indie::ContextManager::displayImage(Image *image, irr::core::position2d<irr::s32> pos, irr::video::SColor color)
{
    irr::core::dimension2d<irr::u32> size = image->getSize();
    irr::core::rect<irr::s32> rect = irr::core::rect<irr::s32>(0, 0, size.Width, size.Height);

    driver->draw2DImage(image, pos, rect, 0, color, true);
}

void Indie::ContextManager::displayImage(Image *image, irr::core::rect<irr::s32> rect, irr::core::position2d<irr::s32> pos, irr::video::SColor color)
{
    driver->draw2DImage(image, pos, rect, 0, color, true);
}
