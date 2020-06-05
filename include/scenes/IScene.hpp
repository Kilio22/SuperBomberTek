/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** IScene
*/

#ifndef ISCENE_HPP_
#define ISCENE_HPP_

#include "ContextManager.hpp"

namespace Indie
{
    /**
     * @brief IScene interface. All scenes must inherit this interface
     */
    class IScene {
        public:
            virtual ~IScene() = default;

            /**
             * @brief Inits the scene
             */
            virtual void init() = 0;

            /**
             * @brief Resets the scene
             */
            virtual void reset() = 0;

            /**
             * @brief Updates the scene
             *
             * @param deltaTime The time elapsed since the last time this method has been called. It's very useful for framerate independence.
             */
            virtual void update(irr::f32 deltaTime) = 0;

            /**
             * @brief Renders before 3D rendering
             */
            virtual void renderPre3D() = 0;

            /**
             * @brief Renders after 3D rendering
             *
             */
            virtual void renderPost3D() = 0;
    };
}

#endif /* !ISCENE_HPP_ */
