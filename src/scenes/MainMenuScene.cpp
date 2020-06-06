/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** MainMenuScene
*/

#include "MainMenuScene.hpp"
#include "EndScene.hpp"
#include "GameScene.hpp"
#include "MultiScene.hpp"
#include "OptionsScene.hpp"
#include "PauseScene.hpp"
#include "Scenes.h"
#include "ServiceLocator.hpp"
#include "ImageLoader.hpp"
#include "SceneManager.hpp"
#include "MusicManager.hpp"

Indie::MainMenuScene::MainMenuScene(ContextManager &context)
    : context(context)
    , selector(1, 5, irr::EKEY_CODE::KEY_UP, irr::EKEY_CODE::KEY_DOWN, irr::EKEY_CODE::KEY_LEFT, irr::EKEY_CODE::KEY_RIGHT)
{
    for (size_t buttonType = (size_t)BUTTON_TYPE::SOLO; buttonType < (size_t)BUTTON_TYPE::NONE; buttonType++) {
        this->buttons.insert({ (BUTTON_TYPE)buttonType, std::make_unique<Button>(context) });
    }
}

void Indie::MainMenuScene::init()
{
    Indie::ServiceLocator::getInstance().get<Indie::MusicManager>().setMusic(0);

    this->title = Indie::ServiceLocator::getInstance().get<Indie::ImageLoader>().getImage("../ressources/images/menu/title.png");
    this->bomb = Indie::ServiceLocator::getInstance().get<Indie::ImageLoader>().getImage("../ressources/images/menu/bomb.png");
    this->buttons.at(BUTTON_TYPE::SOLO)->init(context, "../ressources/images/menu/Solo.png", 0, 0, POS(0, 0));
    this->buttons.at(BUTTON_TYPE::MULTI)->init(context, "../ressources/images/menu/Multi.png", 0, 1, POS(0, 0));
    this->buttons.at(BUTTON_TYPE::OPTIONS)->init(context, "../ressources/images/menu/Options.png", 0, 2, POS(0, 0));
    this->buttons.at(BUTTON_TYPE::CREDITS)->init(context, "../ressources/images/menu/Credits.png", 0, 3, POS(0, 0));
    this->buttons.at(BUTTON_TYPE::QUITTER)->init(context, "../ressources/images/menu/Quitter.png", 0, 4, POS(0, 0));
}

void Indie::MainMenuScene::reset()
{
    init();
}

void Indie::MainMenuScene::update(irr::f32)
{
    selector.update();
    for (auto &button : this->buttons) {
        button.second->update(selector.getPos());
    }
    if (this->buttons.at(BUTTON_TYPE::SOLO)->getStatus() == Button::Status::Pressed) {
        ServiceLocator::getInstance().get<Indie::SceneManager>().setSubScene<Indie::SoloScene>();
        skipScene(true, true, true, true);
    }
    if (this->buttons.at(BUTTON_TYPE::MULTI)->getStatus() == Button::Status::Pressed) {
        ServiceLocator::getInstance().get<Indie::SceneManager>().setSubScene<Indie::MultiScene>();
        skipScene(true, true, true, true);
    }
    if (this->buttons.at(BUTTON_TYPE::OPTIONS)->getStatus() == Button::Status::Pressed) {
        ServiceLocator::getInstance().get<Indie::SceneManager>().setSubScene<Indie::OptionsScene>();
        skipScene(true, true, true, true);
    }
    if (this->buttons.at(BUTTON_TYPE::QUITTER)->getStatus() == Button::Status::Pressed) {
        context.getDevice()->closeDevice();
    }
    if (Indie::EventHandler::getInstance().isKeyPressed(irr::KEY_ESCAPE) == true) {
        Indie::ServiceLocator::getInstance().get<Indie::SceneManager>().setSubScene<Indie::TitleScene>();
        Indie::ServiceLocator::getInstance().get<Indie::SceneManager>().setSceneUpdateActive(true);
        Indie::ServiceLocator::getInstance().get<Indie::SceneManager>().setSceneRenderActive(true);
        Indie::ServiceLocator::getInstance().get<Indie::SceneManager>().setSubSceneUpdateActive(true);
        Indie::ServiceLocator::getInstance().get<Indie::SceneManager>().setSubSceneRenderActive(true);
        EventHandler::getInstance().resetKeys();
    }
}

void Indie::MainMenuScene::renderPre3D() {}

void Indie::MainMenuScene::renderPost3D()
{
    for (auto &button : this->buttons) {
        button.second->draw();
    }
    context.displayImage(title);
    context.displayImage(bomb);
}

void Indie::MainMenuScene::skipScene(bool update, bool render, bool subUpdate, bool subRender)
{
    Indie::ServiceLocator::getInstance().get<Indie::SceneManager>().setSceneUpdateActive(update);
    Indie::ServiceLocator::getInstance().get<Indie::SceneManager>().setSceneRenderActive(render);
    Indie::ServiceLocator::getInstance().get<Indie::SceneManager>().setSubSceneUpdateActive(subUpdate);
    Indie::ServiceLocator::getInstance().get<Indie::SceneManager>().setSubSceneRenderActive(subRender);
}