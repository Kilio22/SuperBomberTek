/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** MainMenuScene
*/

#include "MainMenuScene.hpp"
#include "GameScene.hpp"
#include "ServiceLocator.hpp"

// Passer ça en méthode de MainMenuScene ??
static void skipScene(Indie::ContextManager &context)
{
    Indie::ServiceLocator::getInstance().get<Indie::SceneManager>().setScene<Indie::GameScene>(context);
    Indie::ServiceLocator::getInstance().get<Indie::SceneManager>().setSceneUpdateActive(true);
    Indie::ServiceLocator::getInstance().get<Indie::SceneManager>().setSceneRenderActive(true);
    Indie::ServiceLocator::getInstance().get<Indie::SceneManager>().setSubSceneUpdateActive(false);
    Indie::ServiceLocator::getInstance().get<Indie::SceneManager>().setSubSceneRenderActive(false);
}

Indie::MainMenuScene::MainMenuScene(ContextManager &context)
    : context(context), selector(1, 2, irr::EKEY_CODE::KEY_UP, irr::EKEY_CODE::KEY_DOWN, irr::EKEY_CODE::KEY_LEFT, irr::EKEY_CODE::KEY_RIGHT)
{}

Indie::MainMenuScene::~MainMenuScene()
{
}

void Indie::MainMenuScene::init()
{
    Indie::ServiceLocator::getInstance().get<Indie::MusicManager>().setMusic(0);

    std::string path1 = std::string("../ressources/placeholder/jouer.png");
    std::string path2 = std::string("../ressources/placeholder/options.png");

    play.reset(new Button(context));
    options.reset(new Button(context));
    play->init(context, path1, 0, 0, POS(0, 0));
    options->init(context, path2, 0, 1, POS(0, 0));
}

void Indie::MainMenuScene::reset()
{
    selector.setPos(0, 0);
    init();
}

void Indie::MainMenuScene::update(irr::f32 ticks)
{
    selector.update();
    play->update(selector.getPos());
    options->update(selector.getPos());

    if (play->getStatus() == Button::Status::Pressed) {
        skipScene(context);
    }
}

void Indie::MainMenuScene::renderPre3D()
{}

void Indie::MainMenuScene::renderPost3D()
{
    play->draw();
    options->draw();
}