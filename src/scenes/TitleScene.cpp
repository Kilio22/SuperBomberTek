/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** TitleScene
*/

#include "TitleScene.hpp"
#include "Exceptions.h"
#include "MainMenuScene.hpp"

// Passer ça en méthode de TitleScene ??
// putain t'as commenté chaque fichier enfaite.
// oui c'est fait

const double Indie::TitleScene::updateRate = (((2 * M_PI) / 96) / 32) * 3000;

Indie::TitleScene::TitleScene(ContextManager &context)
    : context(context)
{
}

Indie::TitleScene::~TitleScene() {}

void Indie::TitleScene::init()
{
    this->titleLogo = Indie::ServiceLocator::getInstance().get<Indie::ImageLoader>().getImage("../ressources/images/logo.png");
    this->pressText = Indie::ServiceLocator::getInstance().get<Indie::ImageLoader>().getImage("../ressources/images/press.png");
    if (titleLogo == nullptr) {
        throw Exceptions::FileNotFoundException(ERROR_STR, "File \"../ressources/images/logo.png\" not found.");
    }
    if (pressText == nullptr) {
        throw Exceptions::FileNotFoundException(ERROR_STR, "File \"../ressources/images/press.png\" not found.");
    }
    EventHandler::getInstance().resetKeysStatusOnce();
    EventHandler::getInstance().resetKeysStatus();
}

void Indie::TitleScene::reset()
{
    this->offsetY = 0;
    this->offsetAlpha = 0;
    init();
}

void Indie::TitleScene::skipScene(bool update, bool render, bool subUpdate, bool subRender)
{
    Indie::ServiceLocator::getInstance().get<Indie::SceneManager>().setSubScene<Indie::MainMenuScene>();
    Indie::ServiceLocator::getInstance().get<Indie::SceneManager>().setSceneUpdateActive(update);
    Indie::ServiceLocator::getInstance().get<Indie::SceneManager>().setSceneRenderActive(render);
    Indie::ServiceLocator::getInstance().get<Indie::SceneManager>().setSubSceneUpdateActive(subUpdate);
    Indie::ServiceLocator::getInstance().get<Indie::SceneManager>().setSubSceneRenderActive(subRender);
}

void Indie::TitleScene::update(irr::f32 ticks)
{
    if (EventHandler::getInstance().isKeyPressed(irr::KEY_ESCAPE)) {
        this->context.getDevice()->closeDevice();
        return;
    }
    if (EventHandler::getInstance().isAnyKeyPressedAtOnce()) {
        skipScene(true, true, true, true);
    }
    this->offsetY = (this->offsetY < 2 * M_PI) ? this->offsetY + this->updateRate * ticks : 0;
    this->offsetAlpha = (this->offsetAlpha < 2 * M_PI) ? this->offsetAlpha + 3 * ticks : 0;
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
    this->context.displayImage(this->pressText, POS(0, 0), irr::video::SColor((irr::u32)((sin(this->offsetAlpha) + 1) / 2 * 255), 255, 255, 255));
}