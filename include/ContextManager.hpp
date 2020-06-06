/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** ContextManager
*/

#ifndef CONTEXTMANAGER_HPP_
#define CONTEXTMANAGER_HPP_

#include <irrlicht.h>

#define POS(x, y) (irr::core::position2d<irr::s32>((irr::s32)x, (irr::s32)y))
#define RECT(x, y, w, h) (irr::core::rect<irr::s32>((irr::s32)x, (irr::s32)y, (irr::s32)w, (irr::s32)h))
#define DIM(x, y) (irr::core::dimension2d<irr::u32>((irr::s32)x, (irr::s32)y))

using Image = irr::video::ITexture;

namespace Indie
{

    /**
     * @brief ContextManager class
     */
    class ContextManager
    {
    public:
        ContextManager(irr::core::dimension2d<irr::u32> size = DIM(1280, 720));
        ~ContextManager();

        /* Getters */
        /**
         * @brief Gets the device
         * @return irr::IrrlichtDevice* The device
         */
        irr::IrrlichtDevice *getDevice() const
        {
            return device;
        }

        /**
         * @brief Gets the driver
         * @return irr::video::IVideoDriver* The driver
         */
        irr::video::IVideoDriver *getDriver() const
        {
            return driver;
        }

        /**
         * @brief Gets the Scene Manager
         * @return irr::scene::ISceneManager* The scene manager
         */
        irr::scene::ISceneManager *getSceneManager() const
        {
            return sceneManager;
        }

        /**
         * @brief Gets the GUI Environment
         * @return irr::gui::IGUIEnvironment* The GUI Environment
         */
        irr::gui::IGUIEnvironment *getGuiEnv() const
        {
            return guiEnv;
        }

        /* Methods */
        /**
         * @brief Displays an image on the screen
         * @param image The image to display
         * @param pos The position of the image
         * @param color The color of the image
         */
        void displayImage(Image *image, irr::core::position2d<irr::s32> pos = irr::core::position2d<irr::s32>(0, 0),
            irr::video::SColor color = irr::video::SColor(255, 255, 255, 255));

        /**
         * @brief Displays an image on the screen
         * @param image The image to display
         * @param rect Part of the image to display
         * @param pos The position of the image
         * @param color The color of the image
         */
        void displayImage(Image *image, irr::core::rect<irr::s32> rect, irr::core::position2d<irr::s32> pos = irr::core::position2d<irr::s32>(0, 0),
            irr::video::SColor color = irr::video::SColor(255, 255, 255, 255));

    private:
        irr::core::dimension2d<irr::u32> size;
        irr::IrrlichtDevice *device;
        irr::video::IVideoDriver *driver;
        irr::scene::ISceneManager *sceneManager;
        irr::gui::IGUIEnvironment *guiEnv;
    };

}

#endif /* !CONTEXTMANAGER_HPP_ */
