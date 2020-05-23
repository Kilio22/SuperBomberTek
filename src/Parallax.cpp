/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** Parallax
*/

#include "Parallax.hpp"
#include "Exceptions.h"

void Indie::Parallax::init(ContextManager &context, const std::string &filepath, irr::core::position2d<irr::s32> size, irr::core::position2d<float> vel)
{
    image = context.getDriver()->getTexture(filepath.c_str());
    pos = irr::core::position2d<float>(0, 0);
    size = size;
    vel = vel;
    if (!image) {
        throw Exceptions::FileNotFoundException(ERROR_STR, "File \"" + filepath + "\" not found.");
    }
}

void Indie::Parallax::update()
{
    pos.X += vel.X;
    pos.Y += vel.Y;
    pos.X =  (pos.X < -size.X) ? 0 : pos.X;
    pos.Y = (pos.Y < -size.Y) ? 0 : pos.Y;
    pos.X = (pos.X > size.X) ? 0 : pos.X;
    pos.Y = (pos.Y > size.Y) ? 0 : pos.Y;
}

void Indie::Parallax::draw(ContextManager &context)
{
    // All 9 images arround it so you can move the parrallax in any direction seamlessely;
    context.displayImage(image, RECT(0, 0, size.X, size.Y), POS(pos.X - size.X, pos.Y - size.Y));
    context.displayImage(image, RECT(0, 0, size.X, size.Y), POS(pos.X, pos.Y - size.Y));
    context.displayImage(image, RECT(0, 0, size.X, size.Y), POS(pos.X + size.X, pos.Y - size.X));
    context.displayImage(image, RECT(0, 0, size.X, size.Y), POS(pos.X - size.X, pos.Y));
    context.displayImage(image, RECT(0, 0, size.X, size.Y), POS(pos.X, pos.Y));
    context.displayImage(image, RECT(0, 0, size.X, size.Y), POS(pos.X + size.X, pos.Y));
    context.displayImage(image, RECT(0, 0, size.X, size.Y), POS(pos.X - size.X, pos.Y + size.Y));
    context.displayImage(image, RECT(0, 0, size.X, size.Y), POS(pos.X, pos.Y + size.Y));
    context.displayImage(image, RECT(0, 0, size.X, size.Y), POS(pos.X + size.X, pos.Y + size.Y));
}