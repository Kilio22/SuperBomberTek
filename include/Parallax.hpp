/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** Parallax
*/

#ifndef PARALLAX_HPP_
#define PARALLAX_HPP_

#include <iostream>
#include <irrlicht.h>

#include "ContextManager.hpp"

class Parallax {
    public:
        Parallax() {}
        ~Parallax() {}

        bool init(ContextManager &context, const irr::io::path& filepath, irr::core::position2d<irr::s32> _size, irr::core::position2d<float> _vel);
        void update();
        void draw(ContextManager &context);

    private:
        Image *image;
        irr::core::position2d<float> pos;
        irr::core::position2d<irr::s32> size;
        irr::core::position2d<float> vel;
};

#endif /* !PARALLAX_HPP_ */