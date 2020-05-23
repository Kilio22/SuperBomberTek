/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** Parallax
*/

#ifndef PARALLAX_HPP_
#define PARALLAX_HPP_

#include "ContextManager.hpp"
#include <string>
#include <irrlicht.h>

namespace Indie {
    class Parallax {
        public:
            Parallax() = default;
            ~Parallax() = default;

            void init(ContextManager &context, const std::string &filepath, irr::core::position2d<irr::s32> size, irr::core::position2d<float> vel);
            void update();
            void draw(ContextManager &context);

        private:
            Image *image;
            irr::core::position2d<float> pos;
            irr::core::position2d<irr::s32> size;
            irr::core::position2d<float> vel;
    };
}

#endif /* !PARALLAX_HPP_ */