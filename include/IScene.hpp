/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** IScene
*/

#ifndef ISCENE_HPP_
#define ISCENE_HPP_

#include "ContextManager.hpp"
#include "MusicManager.hpp"
class IScene {
    public:
        virtual ~IScene() = default;

        virtual bool init(ContextManager &context) = 0;
        // Returns false if it couldn't load all the ressources needed in the scene properly.
        // Otherwise returns true.
        virtual bool reset(ContextManager &context) = 0;
        // Returns false if it couldn't load all the ressources needed in the scene properly.
        // Otherwise returns true.
        virtual void update() = 0;
        virtual void renderPre3D() = 0;
        virtual void renderPost3D() = 0;
};

#endif /* !ISCENE_HPP_ */
