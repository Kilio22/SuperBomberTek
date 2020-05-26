/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** SplashScene
*/

#include "SplashScene.hpp"
#include "ServiceLocator.hpp"

static void skipScene(Indie::ContextManager &context)
{
    Indie::ServiceLocator::getInstance().get<Indie::SceneManager>().setScene(1, context);
    Indie::ServiceLocator::getInstance().get<Indie::SceneManager>().setSubScene(2);
    Indie::ServiceLocator::getInstance().get<Indie::SceneManager>().setSceneUpdateActive(true);
    Indie::ServiceLocator::getInstance().get<Indie::SceneManager>().setSceneRenderActive(true);
    Indie::ServiceLocator::getInstance().get<Indie::SceneManager>().setSubSceneUpdateActive(true);
    Indie::ServiceLocator::getInstance().get<Indie::SceneManager>().setSubSceneRenderActive(true);
}

Indie::SplashScene::SplashScene(ContextManager &context)
    : context(context)
{}

void Indie::SplashScene::init()
{
    std::string bgPath = "../ressources/placeholder/splashscreen.png";

    Indie::ServiceLocator::getInstance().get<Indie::MusicManager>().setMusic(0);
    background = context.getDriver()->getTexture(bgPath.c_str());
    if (!background)
        throw Exceptions::FileNotFoundException(ERROR_STR, "File \"" + bgPath + "\" not found.");
}

void Indie::SplashScene::reset()
{
    init();
}

void Indie::SplashScene::update(irr::f32)
{
    if (EventHandler::getInstance().isAnyKeyPressedAtOnce()) {
        skipScene(context);
        ServiceLocator::getInstance().get<MusicManager>().setStatus(Music::Status::Loop);
    }
    if (Indie::ServiceLocator::getInstance().get<Indie::MusicManager>().getStatus() == Indie::Music::Status::Loop)
        skipScene(context);
}

void Indie::SplashScene::renderPre3D()
{
    context.displayImage(background, POS(0, 0));
}

void Indie::SplashScene::renderPost3D() {}