/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** ContextManager
*/

#include "ContextManager.hpp"
#include "MusicManager.hpp"
#include "SceneManager.hpp"
#include "DeviceException.hpp"

Indie::ContextManager::ContextManager(irr::core::dimension2d<irr::u32> size)
{
    device = irr::createDevice(irr::video::EDT_OPENGL, size, 32);
    if (device == nullptr) {
        throw Indie::Exceptions::DeviceException(ERROR_STR, "Cannot create device.");
    }
    this->size = size;
    driver = device->getVideoDriver();
    if (driver == nullptr) {
        throw Indie::Exceptions::DeviceException(ERROR_STR, "Cannot get driver.");
    }
    sceneManager = device->getSceneManager();
    if (sceneManager == nullptr) {
        throw Indie::Exceptions::DeviceException(ERROR_STR, "Cannot get scene manager.");
    }
    guiEnv = device->getGUIEnvironment();
    if (guiEnv == nullptr) {
        throw Indie::Exceptions::DeviceException(ERROR_STR, "Cannot get GUI Environment.");
    }
}

Indie::ContextManager::~ContextManager()
{
    device->drop();
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
