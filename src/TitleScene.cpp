/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** TitleScene
*/

#include "Scenes/TitleScene.hpp"

bool TitleScene::init(ContextManager &_context)
{
    titleLogo = _context.getDriver()->getTexture("../ressources/images/logo.png");
    pressText = _context.getDriver()->getTexture("../ressources/images/press.png");
    if (!titleLogo || !pressText)
        return (false);
    this->context = &_context;
    return (true);
}

bool TitleScene::reset(ContextManager &_context)
{
    _context.getDriver()->removeTexture(titleLogo);
    _context.getDriver()->removeTexture(pressText);
    offsetY = 0;
    offsetAlpha = 0;
    return (init(_context));
}

void TitleScene::update()
{
    offsetY = (offsetY < 2 * M_PI) ? offsetY + updateRate : 0;
    offsetAlpha = (offsetAlpha < 2 * M_PI) ? offsetAlpha + 0.001 : 0;
}

void TitleScene::renderPre3D() {}

void TitleScene::renderPost3D()
{
    irr::u32 posY;

    if (sin(offsetY) < 0)
        posY = sin(offsetY) * 20;
    else
        posY = sin(offsetY) * 10;
    context->displayImage(titleLogo, POS(0, posY));
    context->displayImage(pressText, POS(0, 0), irr::video::SColor((sin(offsetAlpha) + 1) / 2 * 255,255,255,255));
}