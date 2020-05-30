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

const std::unordered_map<Indie::PauseScene::PAUSE_ASSETS, std::string> Indie::PauseScene::assets_paths
    = { { Indie::PauseScene::PAUSE_ASSETS::CONTINUE, "../ressources/images/pause/Continue.png" },
          { Indie::PauseScene::PAUSE_ASSETS::MENU, "../ressources/images/pause/Menu.png" },
          { Indie::PauseScene::PAUSE_ASSETS::QUIT, "../ressources/images/pause/Quitter.png" },
          { Indie::PauseScene::PAUSE_ASSETS::RESTART, "../ressources/images/pause/Recommencer.png" },
          { Indie::PauseScene::PAUSE_ASSETS::BOMBER, "../ressources/images/pause/Pause.png" },
          { Indie::PauseScene::PAUSE_ASSETS::TITLE, "../ressources/images/pause/Title.png" },
          { Indie::PauseScene::PAUSE_ASSETS::BG, "../ressources/images/black_bg.png" } };

Indie::PauseScene::PauseScene(ContextManager &context)
    : context(context), selector(1, 4, irr::EKEY_CODE::KEY_UP, irr::EKEY_CODE::KEY_DOWN, irr::EKEY_CODE::KEY_LEFT, irr::EKEY_CODE::KEY_RIGHT)
{
}

Indie::PauseScene::~PauseScene()
{
    if (this->bomber)
        this->context.getDriver()->removeTexture(this->bomber);
    if (this->title)
        this->context.getDriver()->removeTexture(this->title);
    if (this->bg)
        this->context.getDriver()->removeTexture(this->bg);
}

void Indie::PauseScene::init()
{
    this->play.reset(new Button(context));
    this->menu.reset(new Button(context));
    this->quit.reset(new Button(context));
    this->restart.reset(new Button(context));
    this->play->init(context, this->assets_paths.at(Indie::PauseScene::PAUSE_ASSETS::CONTINUE), 0, 0, POS(0, 0));
    this->restart->init(context, this->assets_paths.at(Indie::PauseScene::PAUSE_ASSETS::RESTART), 0, 1, POS(0, 0));
    this->menu->init(context, this->assets_paths.at(Indie::PauseScene::PAUSE_ASSETS::MENU), 0, 2, POS(0, 0));
    this->quit->init(context, this->assets_paths.at(Indie::PauseScene::PAUSE_ASSETS::QUIT), 0, 3, POS(0, 0));
    this->bomber = context.getDriver()->getTexture(this->assets_paths.at(Indie::PauseScene::PAUSE_ASSETS::BOMBER).c_str());
    if (this->bomber == nullptr) {
        throw Exceptions::FileNotFoundException(
            ERROR_STR, "File \"" + this->assets_paths.at(Indie::PauseScene::PAUSE_ASSETS::BOMBER) + "\" not found.");
    }
    this->title = context.getDriver()->getTexture(this->assets_paths.at(Indie::PauseScene::PAUSE_ASSETS::TITLE).c_str());
    if (this->title == nullptr) {
        throw Exceptions::FileNotFoundException(
            ERROR_STR, "File \"" + this->assets_paths.at(Indie::PauseScene::PAUSE_ASSETS::TITLE) + "\" not found.");
    }
    this->bg = context.getDriver()->getTexture(this->assets_paths.at(Indie::PauseScene::PAUSE_ASSETS::BG).c_str());
    if (this->bg == nullptr) {
        throw Exceptions::FileNotFoundException(ERROR_STR, "File \"" + this->assets_paths.at(Indie::PauseScene::PAUSE_ASSETS::BG) + "\" not found.");
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

    if (this->play->getStatus() == Button::Status::Pressed || Indie::EventHandler::getInstance().isKeyPressed(irr::KEY_ESCAPE) == true) {
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
    // TODO : à tester si ça nique rien
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
