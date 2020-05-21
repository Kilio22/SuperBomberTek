/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** Parallax
*/

#include "Parallax.hpp"

bool Parallax::init(ContextManager &context, const irr::io::path &filepath, irr::core::position2d<irr::s32> _size, irr::core::position2d<float> _vel)
{
    image = context.getDriver()->getTexture(filepath);
    pos = irr::core::position2d<float>(0, 0);
    size = _size;
    vel = _vel;
    if (!image)
        return (false);
    return (true);
}

void Parallax::update()
{
    pos.X += vel.X;
    pos.Y += vel.Y;
    pos.X =  (pos.X < -size.X) ? 0 : pos.X;
    pos.Y = (pos.Y < -size.Y) ? 0 : pos.Y;
    pos.X = (pos.X > size.X) ? 0 : pos.X;
    pos.Y = (pos.Y > size.Y) ? 0 : pos.Y;
}

void Parallax::draw(ContextManager &context)
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