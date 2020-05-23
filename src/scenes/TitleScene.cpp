/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** TitleScene
*/

#include "TitleScene.hpp"
#include "Exceptions.h"

const double Indie::TitleScene::updateRate = ((2 * M_PI) / 96) / 32;

Indie::TitleScene::TitleScene(ContextManager &context)
    : context(context)
{}

void Indie::TitleScene::init()
{
    this->titleLogo = this->context.getDriver()->getTexture("../ressources/images/logo.png");
    this->pressText = this->context.getDriver()->getTexture("../ressources/images/press.png");
    if (titleLogo == nullptr) {
        throw Exceptions::FileNotFoundException(ERROR_STR, "File \"../ressources/images/logo.png\" not found.");
    }
    if (pressText == nullptr) {
        throw Exceptions::FileNotFoundException(ERROR_STR, "File \"../ressources/images/press.png\" not found.");
    }
}

void Indie::TitleScene::reset()
{
    this->context.getDriver()->removeTexture(titleLogo);
    this->context.getDriver()->removeTexture(pressText);
    this->offsetY = 0;
    this->offsetAlpha = 0;
    init();
}

void Indie::TitleScene::update(irr::f32)
{
    this->offsetY = (this->offsetY < 2 * M_PI) ? this->offsetY + this->updateRate : 0;
    this->offsetAlpha = (this->offsetAlpha < 2 * M_PI) ? this->offsetAlpha + 0.001 : 0;
}

void Indie::TitleScene::renderPre3D() {}

void Indie::TitleScene::renderPost3D()
{
    irr::u32 posY;

    if (sin(this->offsetY) < 0)
        posY = (irr::u32)(sin(this->offsetY) * 20);
    else
        posY = (irr::u32)(sin(this->offsetY) * 10);
    this->context.displayImage(this->titleLogo, POS(0, posY));
    this->context.displayImage(this->pressText, POS(0, 0), irr::video::SColor((irr::u32)((sin(this->offsetAlpha) + 1) / 2 * 255),255,255,255));
}