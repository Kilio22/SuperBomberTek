/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** ContextManager
*/

#ifndef CONTEXTMANAGER_HPP_
#define CONTEXTMANAGER_HPP_

#include <irrlicht.h>
#include <iostream>

#define POS(x, y) (irr::core::position2d<irr::s32>((irr::s32)x,(irr::s32)y))
#define RECT(x, y, w, h) (irr::core::rect<irr::s32>((irr::s32)x, (irr::s32)y, (irr::s32)w, (irr::s32)h))

typedef irr::video::ITexture Image;

class ContextManager {
    public:
        ContextManager(irr::core::dimension2d<irr::u32> size);
        ~ContextManager();

        /* Getters */
        irr::IrrlichtDevice *getDevice() const {return (device);}
        irr::video::IVideoDriver *getDriver() const {return (driver);}
        irr::scene::ISceneManager *getSceneManager() const {return (sceneManager);}
        irr::gui::IGUIEnvironment *getGuiEnv() const {return (guiEnv);}

        /* Methods */
        void displayImage(irr::video::ITexture *image, irr::core::position2d<irr::s32> pos = irr::core::position2d<irr::s32>(0,0), irr::video::SColor color = irr::video::SColor(255,255,255,255));
        void displayImage(irr::video::ITexture *image, irr::core::rect<irr::s32> rect, irr::core::position2d<irr::s32> pos = irr::core::position2d<irr::s32>(0,0), irr::video::SColor color = irr::video::SColor(255,255,255,255));

    private:
        irr::core::dimension2d<irr::u32> size;
        irr::IrrlichtDevice *device;
        irr::video::IVideoDriver *driver;
        irr::scene::ISceneManager *sceneManager;
        irr::gui::IGUIEnvironment *guiEnv;
};

#endif /* !CONTEXTMANAGER_HPP_ */
