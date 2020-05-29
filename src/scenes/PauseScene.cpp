/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** PauseScene | Author: Kylian BALAN - kylian.balan@epitech.eu
*/

#include "PauseScene.hpp"
#include "GameScene.hpp"
#include "Scenes.hpp"
#include "ServiceLocator.hpp"

Indie::PauseScene::PauseScene(ContextManager &context)
    : context(context), selector(1, 4, irr::EKEY_CODE::KEY_UP, irr::EKEY_CODE::KEY_DOWN, irr::EKEY_CODE::KEY_LEFT, irr::EKEY_CODE::KEY_RIGHT)
{
}

void Indie::PauseScene::init()
{
    std::string continuePath = std::string("../ressources/images/pause/Continue.png");
    std::string menuPath = std::string("../ressources/images/pause/Menu.png");
    std::string quitPath = std::string("../ressources/images/pause/Quitter.png");
    std::string restartPath = std::string("../ressources/images/pause/Recommencer.png");
    std::string bomberPath = std::string("../ressources/images/pause/Pause.png");
    std::string titlePath = std::string("../ressources/images/pause/Title.png");

    this->play.reset(new Button(context));
    this->menu.reset(new Button(context));
    this->quit.reset(new Button(context));
    this->restart.reset(new Button(context));
    this->play->init(context, continuePath, 0, 0, POS(0, 0));
    this->restart->init(context, restartPath, 0, 1, POS(0, 0));
    this->menu->init(context, menuPath, 0, 2, POS(0, 0));
    this->quit->init(context, quitPath, 0, 3, POS(0, 0));
    this->bomber = context.getDriver()->getTexture(bomberPath.c_str());
    if (this->bomber == nullptr) {
        throw Exceptions::FileNotFoundException(ERROR_STR, "File \"" + bomberPath + "\" not found.");
    }
    this->title = context.getDriver()->getTexture(titlePath.c_str());
    if (this->title == nullptr) {
        throw Exceptions::FileNotFoundException(ERROR_STR, "File \"" + titlePath + "\" not found.");
    }
}

void Indie::PauseScene::reset()
{
    this->selector.setPos(0, 0);
    this->init();
}

void Indie::PauseScene::update(irr::f32)
{
    this->selector.update();
    this->play->update(this->selector.getPos());
    this->menu->update(this->selector.getPos());
    this->quit->update(this->selector.getPos());
    this->restart->update(this->selector.getPos());

    if (this->play->getStatus() == Button::Status::Pressed) {
        Indie::ServiceLocator::getInstance().get<Indie::SceneManager>().setSubSceneUpdateActive(false);
        Indie::ServiceLocator::getInstance().get<Indie::SceneManager>().setSubSceneRenderActive(false);
        Indie::ServiceLocator::getInstance().get<Indie::SceneManager>().setSceneUpdateActive(true);
        Indie::ServiceLocator::getInstance().get<Indie::SceneManager>().setSceneRenderActive(true);
    }
    if (this->quit->getStatus() == Button::Status::Pressed) {
        this->context.getDevice()->closeDevice();
    }
    if (this->menu->getStatus() == Button::Status::Pressed) {
        ServiceLocator::getInstance().get<EntityManager>().reset();
        Indie::ServiceLocator::getInstance().get<Indie::SceneManager>().setScene<Indie::MenuScene>(context);
        Indie::ServiceLocator::getInstance().get<Indie::SceneManager>().setSubScene<Indie::MainMenuScene>();
    }
    if (this->restart->getStatus() == Button::Status::Pressed) {
        ServiceLocator::getInstance().get<EntityManager>().reset();
        Indie::ServiceLocator::getInstance().get<Indie::SceneManager>().getScene<Indie::GameScene>()->reset();
        Indie::ServiceLocator::getInstance().get<Indie::SceneManager>().setSceneUpdateActive(true);
        Indie::ServiceLocator::getInstance().get<Indie::SceneManager>().setSceneRenderActive(true);
        Indie::ServiceLocator::getInstance().get<Indie::SceneManager>().setSubSceneUpdateActive(false);
        Indie::ServiceLocator::getInstance().get<Indie::SceneManager>().setSubSceneRenderActive(false);
    }
}

void Indie::PauseScene::renderPre3D() {}

void Indie::PauseScene::renderPost3D()
{
    this->play->draw();
    this->menu->draw();
    this->quit->draw();
    this->restart->draw();
    this->context.displayImage(this->bomber);
    this->context.displayImage(this->title);
}
