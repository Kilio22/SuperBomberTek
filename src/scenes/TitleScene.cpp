/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** TitleScene
*/

#include "TitleScene.hpp"

const double Indie::TitleScene::updateRate = ((2 * M_PI) / 96) / 32;

bool Indie::TitleScene::init(ContextManager &_context)
{
    titleLogo = _context.getDriver()->getTexture("../ressources/images/logo.png");
    pressText = _context.getDriver()->getTexture("../ressources/images/press.png");
    if (!titleLogo || !pressText)
        return (false);
    this->context = &_context;
    return (true);
}

bool Indie::TitleScene::reset(ContextManager &_context)
{
    _context.getDriver()->removeTexture(titleLogo);
    _context.getDriver()->removeTexture(pressText);
    offsetY = 0;
    offsetAlpha = 0;
    return (init(_context));
}

void Indie::TitleScene::update(irr::f32 deltaTime)
{
    offsetY = (offsetY < 2 * M_PI) ? offsetY + updateRate : 0;
    offsetAlpha = (offsetAlpha < 2 * M_PI) ? offsetAlpha + 0.001 : 0;
}

void Indie::TitleScene::renderPre3D() {}

void Indie::TitleScene::renderPost3D()
{
    irr::u32 posY;

    if (sin(offsetY) < 0)
        posY = (irr::u32)(sin(offsetY) * 20);
    else
        posY = (irr::u32)(sin(offsetY) * 10);
    context->displayImage(titleLogo, POS(0, posY));
    context->displayImage(pressText, POS(0, 0), irr::video::SColor((irr::u32)((sin(offsetAlpha) + 1) / 2 * 255),255,255,255));
}