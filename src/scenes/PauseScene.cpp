/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** PauseScene | Author: Kylian BALAN - kylian.balan@epitech.eu
*/

#include "PauseScene.hpp"
#include "Components.h"
#include "GameScene.hpp"
#include "Scenes.h"
#include "ServiceLocator.hpp"
#include "ImageLoader.hpp"
#include "SceneManager.hpp"
#include "SoundManager.hpp"

const std::unordered_map<Indie::PauseScene::PAUSE_ASSETS, std::string> Indie::PauseScene::assets_paths
    = { { Indie::PauseScene::PAUSE_ASSETS::CONTINUE, "../ressources/images/pause/Continue.png" },
          { Indie::PauseScene::PAUSE_ASSETS::MENU, "../ressources/images/pause/Menu.png" },
          { Indie::PauseScene::PAUSE_ASSETS::QUIT, "../ressources/images/pause/Quitter.png" },
          { Indie::PauseScene::PAUSE_ASSETS::RESTART, "../ressources/images/pause/Recommencer.png" },
          { Indie::PauseScene::PAUSE_ASSETS::BOMBER, "../ressources/images/pause/Pause.png" },
          { Indie::PauseScene::PAUSE_ASSETS::TITLE, "../ressources/images/pause/Title.png" },
          { Indie::PauseScene::PAUSE_ASSETS::BG, "../ressources/images/black_bg.png" } };

Indie::PauseScene::PauseScene(ContextManager &context)
    : context(context)
    , selector(1, 4, irr::EKEY_CODE::KEY_UP, irr::EKEY_CODE::KEY_DOWN, irr::EKEY_CODE::KEY_LEFT, irr::EKEY_CODE::KEY_RIGHT)
{
    for (size_t buttonType = (size_t)BUTTON_TYPE::PLAY; buttonType < (size_t)BUTTON_TYPE::NONE; buttonType++) {
        this->buttons.insert({ (BUTTON_TYPE)buttonType, std::make_unique<Button>(context) });
    }
}

void Indie::PauseScene::init()
{
    this->buttons.at(BUTTON_TYPE::PLAY)->init(context, this->assets_paths.at(Indie::PauseScene::PAUSE_ASSETS::CONTINUE), 0, 0, POS(0, 0));
    this->buttons.at(BUTTON_TYPE::RESTART)->init(context, this->assets_paths.at(Indie::PauseScene::PAUSE_ASSETS::RESTART), 0, 1, POS(0, 0));
    this->buttons.at(BUTTON_TYPE::MENU)->init(context, this->assets_paths.at(Indie::PauseScene::PAUSE_ASSETS::MENU), 0, 2, POS(0, 0));
    this->buttons.at(BUTTON_TYPE::QUIT)->init(context, this->assets_paths.at(Indie::PauseScene::PAUSE_ASSETS::QUIT), 0, 3, POS(0, 0));
    this->bomber = Indie::ServiceLocator::getInstance().get<Indie::ImageLoader>().getImage(
        this->assets_paths.at(Indie::PauseScene::PAUSE_ASSETS::BOMBER).c_str());
    this->title = Indie::ServiceLocator::getInstance().get<Indie::ImageLoader>().getImage(
        this->assets_paths.at(Indie::PauseScene::PAUSE_ASSETS::TITLE).c_str());
    this->bg
        = Indie::ServiceLocator::getInstance().get<Indie::ImageLoader>().getImage(this->assets_paths.at(Indie::PauseScene::PAUSE_ASSETS::BG).c_str());
}

void Indie::PauseScene::reset()
{
    this->selector.setPos(0, 0);
    this->init();
}

void Indie::PauseScene::update(irr::f32)
{
    this->selector.update();
    for (const auto &button : this->buttons) {
        button.second->update(this->selector.getPos());
    }
    if (this->buttons[BUTTON_TYPE::PLAY]->getStatus() == Button::Status::Pressed || Indie::EventHandler::getInstance().isKeyPressed(irr::KEY_ESCAPE) == true) {
        ServiceLocator::getInstance().get<SoundManager>().playSound("menu_back");
        Indie::ServiceLocator::getInstance().get<SceneManager>().setSubSceneUpdateActive(false);
        Indie::ServiceLocator::getInstance().get<SceneManager>().setSubSceneRenderActive(false);
        Indie::ServiceLocator::getInstance().get<SceneManager>().setSceneUpdateActive(true);
        Indie::ServiceLocator::getInstance().get<SceneManager>().setSceneRenderActive(true);
        for (auto entity : ServiceLocator::getInstance().get<EntityManager>().each<Components::RenderComponent>()) {
            entity->getComponent<Components::RenderComponent>()->getMesh()->setAnimationSpeed(25.f);
        }
        EventHandler::getInstance().resetKeys();
    }
    if (this->buttons[BUTTON_TYPE::QUIT]->getStatus() == Button::Status::Pressed) {
        this->context.getDevice()->closeDevice();
    }
    if (this->buttons[BUTTON_TYPE::MENU]->getStatus() == Button::Status::Pressed) {
        ServiceLocator::getInstance().get<EntityManager>().reset();
        Indie::ServiceLocator::getInstance().get<SceneManager>().setScene<MenuScene>(context);
        Indie::ServiceLocator::getInstance().get<SceneManager>().setSubScene<MainMenuScene>();
        EventHandler::getInstance().resetKeys();
    }
    if (this->buttons[BUTTON_TYPE::RESTART]->getStatus() == Button::Status::Pressed) {
        ServiceLocator::getInstance().get<EntityManager>().reset();
        Indie::ServiceLocator::getInstance().get<SceneManager>().getScene<GameScene>()->reset();
        Indie::ServiceLocator::getInstance().get<SceneManager>().setSceneUpdateActive(false);
        Indie::ServiceLocator::getInstance().get<SceneManager>().setSceneRenderActive(true);
        Indie::ServiceLocator::getInstance().get<SceneManager>().setSubScene<IntroScene>();
        Indie::ServiceLocator::getInstance().get<SceneManager>().setSubSceneUpdateActive(true);
        Indie::ServiceLocator::getInstance().get<SceneManager>().setSubSceneRenderActive(true);
        Indie::ServiceLocator::getInstance().get<SceneManager>().getScene<IntroScene>()->skipScene();
        EventHandler::getInstance().resetKeys();
    }
}

void Indie::PauseScene::renderPre3D() {}

void Indie::PauseScene::renderPost3D()
{
    this->context.displayImage(this->bg);
    for (const auto &button : this->buttons) {
        button.second->draw();
    }
    this->context.displayImage(this->bomber);
    this->context.displayImage(this->title);
}
