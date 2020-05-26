/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** Parallax
*/

#include "Parallax.hpp"
#include "Exceptions.h"

Indie::Parallax::Parallax(ContextManager &context) : context(context)
{
    image = NULL;
}

Indie::Parallax::~Parallax()
{
    if (image)
        context.getDriver()->removeTexture(image);
}

void Indie::Parallax::init(ContextManager &context, const std::string &filepath, irr::core::position2d<irr::s32> size, irr::core::position2d<float> vel)
{
    image = context.getDriver()->getTexture(filepath.c_str());
    this->context = context;
    pos = irr::core::position2d<float>(0, 0);
    this->size = size;
    this->vel = vel;
    if (!image) {
        throw Exceptions::FileNotFoundException(ERROR_STR, "File \"" + filepath + "\" not found.");
    }
    color = irr::video::SColor(255,255,255,255);
}

void Indie::Parallax::update(irr::f32 ticks)
{
    pos.X += vel.X * ticks;
    pos.Y += vel.Y * ticks;
    pos.X =  (pos.X < -size.X) ? 0 : pos.X;
    pos.Y = (pos.Y < -size.Y) ? 0 : pos.Y;
    pos.X = (pos.X > size.X) ? 0 : pos.X;
    pos.Y = (pos.Y > size.Y) ? 0 : pos.Y;
}

void Indie::Parallax::setColor(irr::video::SColor color)
{
    this->color = color;
}

void Indie::Parallax::draw()
{
    // All 9 images arround it so you can move the parrallax in any direction seamlessely;
    this->context.displayImage(image, RECT(0, 0, size.X, size.Y), POS(pos.X - size.X, pos.Y - size.Y), color);
    this->context.displayImage(image, RECT(0, 0, size.X, size.Y), POS(pos.X, pos.Y - size.Y), color);
    this->context.displayImage(image, RECT(0, 0, size.X, size.Y), POS(pos.X + size.X, pos.Y - size.X), color);
    this->context.displayImage(image, RECT(0, 0, size.X, size.Y), POS(pos.X - size.X, pos.Y), color);
    this->context.displayImage(image, RECT(0, 0, size.X, size.Y), POS(pos.X, pos.Y), color);
    this->context.displayImage(image, RECT(0, 0, size.X, size.Y), POS(pos.X + size.X, pos.Y), color);
    this->context.displayImage(image, RECT(0, 0, size.X, size.Y), POS(pos.X - size.X, pos.Y + size.Y), color);
    this->context.displayImage(image, RECT(0, 0, size.X, size.Y), POS(pos.X, pos.Y + size.Y), color);
    this->context.displayImage(image, RECT(0, 0, size.X, size.Y), POS(pos.X + size.X, pos.Y + size.Y), color);
}