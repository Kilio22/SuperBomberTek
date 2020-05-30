/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** MainMenuScene
*/

#include "MainMenuScene.hpp"
#include "GameScene.hpp"
#include "PauseScene.hpp"
#include "OptionsScene.hpp"
#include "ServiceLocator.hpp"

// Passer ça en méthode de MainMenuScene ??
// C'est fait!
void Indie::MainMenuScene::skipScene(bool update, bool render, bool subUpdate, bool subRender)
{
    Indie::ServiceLocator::getInstance().get<Indie::SceneManager>().setSceneUpdateActive(update);
    Indie::ServiceLocator::getInstance().get<Indie::SceneManager>().setSceneRenderActive(render);
    Indie::ServiceLocator::getInstance().get<Indie::SceneManager>().setSubSceneUpdateActive(subUpdate);
    Indie::ServiceLocator::getInstance().get<Indie::SceneManager>().setSubSceneRenderActive(subRender);
}

Indie::MainMenuScene::MainMenuScene(ContextManager &context)
    : context(context), selector(1, 5, irr::EKEY_CODE::KEY_UP, irr::EKEY_CODE::KEY_DOWN, irr::EKEY_CODE::KEY_LEFT, irr::EKEY_CODE::KEY_RIGHT)
{}

Indie::MainMenuScene::~MainMenuScene()
{
    if (title)
        context.getDriver()->removeTexture(title);
    if (bomb)
        context.getDriver()->removeTexture(bomb);
}

void Indie::MainMenuScene::init()
{
    Indie::ServiceLocator::getInstance().get<Indie::MusicManager>().setMusic(0);

    std::string path1 = std::string("../ressources/images/menu/Solo.png");
    std::string path2 = std::string("../ressources/images/menu/Multi.png");
    std::string path3 = std::string("../ressources/images/menu/Options.png");
    std::string path4 = std::string("../ressources/images/menu/Credits.png");
    std::string path5 = std::string("../ressources/images/menu/Quitter.png");

    title = context.getDriver()->getTexture("../ressources/images/menu/title.png");
    bomb = context.getDriver()->getTexture("../ressources/images/menu/bomb.png");
    solo.reset(new Button(context));
    multi.reset(new Button(context));
    options.reset(new Button(context));
    credits.reset(new Button(context));
    quitter.reset(new Button(context));
    solo->init(context, path1, 0, 0, POS(0, 0));
    multi->init(context, path2, 0, 1, POS(0, 0));
    options->init(context, path3, 0, 2, POS(0, 0));
    credits->init(context, path4, 0, 3, POS(0, 0));
    quitter->init(context, path5, 0, 4, POS(0, 0));
}

void Indie::MainMenuScene::reset()
{
    selector.setPos(0, 0);
    if (title)
        context.getDriver()->removeTexture(title);
    if (bomb)
        context.getDriver()->removeTexture(bomb);
    init();
}

void Indie::MainMenuScene::update(irr::f32 ticks)
{
    selector.update();
    solo->update(selector.getPos());
    multi->update(selector.getPos());
    options->update(selector.getPos());
    credits->update(selector.getPos());
    quitter->update(selector.getPos());

    if (solo->getStatus() == Button::Status::Pressed) {
        ServiceLocator::getInstance().get<Indie::SceneManager>().setScene<Indie::GameScene>(context);
        ServiceLocator::getInstance().get<Indie::SceneManager>().setSubScene<Indie::PauseScene>();
        skipScene(true, true, false, false);
    }
    if (options->getStatus() == Button::Status::Pressed) {
        ServiceLocator::getInstance().get<Indie::SceneManager>().setSubScene<Indie::OptionsScene>();
        skipScene(true, true, true, true);
    }
    if (quitter->getStatus() == Button::Status::Pressed) {
        context.getDevice()->closeDevice();
    }
    EventHandler::getInstance().resetKeysStatusOnce();
    EventHandler::getInstance().resetKeysStatus();
}

void Indie::MainMenuScene::renderPre3D()
{}

void Indie::MainMenuScene::renderPost3D()
{
    solo->draw();
    multi->draw();
    options->draw();
    credits->draw();
    quitter->draw();
    context.displayImage(title);
    context.displayImage(bomb);
}