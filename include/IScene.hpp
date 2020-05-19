/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** IScene
*/

#ifndef ISCENE_HPP_
#define ISCENE_HPP_

#include "ContextManager.hpp"

class IScene {
    public:
        virtual ~IScene() = default;

        virtual void init(ContextManager context) = 0;
        virtual void reset() = 0;
        virtual void update() = 0;
        virtual void renderPre3D() const = 0;
        virtual void renderPost3D() const = 0;
};

#endif /* !ISCENE_HPP_ */
