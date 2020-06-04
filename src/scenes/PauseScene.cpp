/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** PauseScene | Author: Kylian BALAN - kylian.balan@epitech.eu
*/

#include "PauseScene.hpp"
#include "Components.h"
#include "GameScene.hpp"
#include "Scenes.hpp"
#include "ServiceLocator.hpp"

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
    , play(std::make_unique<Button>(context))
    , menu(std::make_unique<Button>(context))
    , quit(std::make_unique<Button>(context))
    , restart(std::make_unique<Button>(context))
{
}

Indie::PauseScene::~PauseScene() {}

void Indie::PauseScene::init()
{
    this->play->init(context, this->assets_paths.at(Indie::PauseScene::PAUSE_ASSETS::CONTINUE), 0, 0, POS(0, 0));
    this->restart->init(context, this->assets_paths.at(Indie::PauseScene::PAUSE_ASSETS::RESTART), 0, 1, POS(0, 0));
    this->menu->init(context, this->assets_paths.at(Indie::PauseScene::PAUSE_ASSETS::MENU), 0, 2, POS(0, 0));
    this->quit->init(context, this->assets_paths.at(Indie::PauseScene::PAUSE_ASSETS::QUIT), 0, 3, POS(0, 0));
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
    this->play->update(this->selector.getPos());
    this->menu->update(this->selector.getPos());
    this->quit->update(this->selector.getPos());
    this->restart->update(this->selector.getPos());

    if (this->play->getStatus() == Button::Status::Pressed || Indie::EventHandler::getInstance().isKeyPressed(irr::KEY_ESCAPE) == true) {
        Indie::ServiceLocator::getInstance().get<Indie::SceneManager>().setSubSceneUpdateActive(false);
        Indie::ServiceLocator::getInstance().get<Indie::SceneManager>().setSubSceneRenderActive(false);
        Indie::ServiceLocator::getInstance().get<Indie::SceneManager>().setSceneUpdateActive(true);
        Indie::ServiceLocator::getInstance().get<Indie::SceneManager>().setSceneRenderActive(true);
        for (auto entity : ServiceLocator::getInstance().get<EntityManager>().each<Components::RenderComponent>()) {
            entity->getComponent<Components::RenderComponent>()->getMesh()->setAnimationSpeed(25.f);
        }
        EventHandler::getInstance().resetKeys();
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
        Indie::ServiceLocator::getInstance().get<Indie::SceneManager>().setSceneUpdateActive(false);
        Indie::ServiceLocator::getInstance().get<Indie::SceneManager>().setSceneRenderActive(true);
        Indie::ServiceLocator::getInstance().get<Indie::SceneManager>().setSubScene<Indie::IntroScene>();
        Indie::ServiceLocator::getInstance().get<Indie::SceneManager>().setSubSceneUpdateActive(true);
        Indie::ServiceLocator::getInstance().get<Indie::SceneManager>().setSubSceneRenderActive(true);
        Indie::ServiceLocator::getInstance().get<Indie::SceneManager>().getScene<IntroScene>()->skipScene();
        EventHandler::getInstance().resetKeys();
    }
    EventHandler::getInstance().resetKeysStatusOnce();
    EventHandler::getInstance().resetKeysStatus();
}

void Indie::PauseScene::renderPre3D() {}

void Indie::PauseScene::renderPost3D()
{
    this->context.displayImage(this->bg);
    this->play->draw();
    this->menu->draw();
    this->quit->draw();
    this->restart->draw();
    this->context.displayImage(this->bomber);
    this->context.displayImage(this->title);
}
