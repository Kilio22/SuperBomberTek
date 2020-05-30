/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** OptionsScene
*/

#include "OptionsScene.hpp"
#include "ServiceLocator.hpp"
#include "MainMenuScene.hpp"

void Indie::OptionsScene::skipScene(bool update, bool render, bool subUpdate, bool subRender)
{
    Indie::ServiceLocator::getInstance().get<Indie::SceneManager>().setSceneUpdateActive(update);
    Indie::ServiceLocator::getInstance().get<Indie::SceneManager>().setSceneRenderActive(render);
    Indie::ServiceLocator::getInstance().get<Indie::SceneManager>().setSubSceneUpdateActive(subUpdate);
    Indie::ServiceLocator::getInstance().get<Indie::SceneManager>().setSubSceneRenderActive(subRender);
}

Indie::OptionsScene::OptionsScene(Indie::ContextManager &context) :
context(context),
selector(1, 5, irr::EKEY_CODE::KEY_UP, irr::EKEY_CODE::KEY_DOWN, irr::EKEY_CODE::KEY_LEFT, irr::EKEY_CODE::KEY_RIGHT),
musicVolumeSelector(25, 1, irr::EKEY_CODE::KEY_UP, irr::EKEY_CODE::KEY_DOWN, irr::EKEY_CODE::KEY_LEFT, irr::EKEY_CODE::KEY_RIGHT),
soundVolumeSelector(25, 1, irr::EKEY_CODE::KEY_UP, irr::EKEY_CODE::KEY_DOWN, irr::EKEY_CODE::KEY_LEFT, irr::EKEY_CODE::KEY_RIGHT)
{}

Indie::OptionsScene::~OptionsScene()
{
    if (title)
        context.getDriver()->removeTexture(title);
    if (wrench)
        context.getDriver()->removeTexture(wrench);
    if (layout)
        context.getDriver()->removeTexture(layout);
}

void Indie::OptionsScene::init()
{
    std::string path1 = std::string("../ressources/images/options/Vol2.png");
    std::string path2 = std::string("../ressources/images/options/Check2.png");
    std::string path3 = std::string("../ressources/images/options/Vol1.png");
    std::string path4 = std::string("../ressources/images/options/Check1.png");
    std::string path5 = std::string("../ressources/images/options/Retour.png");

    title = context.getDriver()->getTexture("../ressources/images/options/title.png");
    wrench = context.getDriver()->getTexture("../ressources/images/options/drawing.png");
    layout = context.getDriver()->getTexture("../ressources/images/options/Layout.png");

    back.reset(new Button(context));
    musicVolume.reset(new Button(context));
    soundVolume.reset(new Button(context));
    musicMute.reset(new Checkbox(context));
    soundMute.reset(new Checkbox(context));

    musicVolume->init(context, path1, 0, 0, POS(0, 0));
    musicMute->init(path2, 0, 1, POS(0, 0));
    soundVolume->init(context, path3, 0, 2, POS(0, 0));
    soundMute->init(path4, 0, 3, POS(0, 0));
    back->init(context, path5, 0, 4, POS(0, 0));

    musicMute->setStatus(Indie::ServiceLocator::getInstance().get<Indie::MusicManager>().isMusicMuted());
    // TODO : Set the sound checkbox status to the isMuted value of the sound when it's done
}

void Indie::OptionsScene::reset()
{
    selector.setPos(0, 0);
    if (title)
        context.getDriver()->removeTexture(title);
    if (wrench)
        context.getDriver()->removeTexture(wrench);
    if (layout)
        context.getDriver()->removeTexture(layout);
    init();
}

void Indie::OptionsScene::update(irr::f32 ticks)
{
    selector.update();
    back->update(selector.getPos());
    musicVolume->update(selector.getPos());
    soundVolume->update(selector.getPos());
    musicMute->update(selector.getPos());
    soundMute->update(selector.getPos());
    if (back->getStatus() == Button::Status::Pressed) {
        ServiceLocator::getInstance().get<Indie::SceneManager>().setSubScene<Indie::MainMenuScene>();
        skipScene(true, true, true, true);
    }
    if (musicMute->getStatus()) {
        Indie::ServiceLocator::getInstance().get<Indie::MusicManager>().mute();
    } else {
        Indie::ServiceLocator::getInstance().get<Indie::MusicManager>().unMute();
    }
    if (soundMute->getStatus()) {
        // TODO : Mute sounds
    } else {
        // TODO : Unmute sounds
    }
    if (musicVolume->getStatus() == Button::Status::Selected) {
        musicVolumeSelector.update();
    }
    if (soundVolume->getStatus() == Button::Status::Selected) {
        soundVolumeSelector.update();
        // TODO : set sound volume
        // Volume =  soundVolumeSelector.getPos().first * 5
    }
    //Indie::ServiceLocator::getInstance().get<Indie::MusicManager>().setVolume(float(musicVolumeSelector.getPos().first * 5));
    Indie::ServiceLocator::getInstance().get<Indie::MusicManager>().setVolume(float(musicVolumeSelector.getPos().first));
    EventHandler::getInstance().resetKeysStatusOnce();
    EventHandler::getInstance().resetKeysStatus();
}

void Indie::OptionsScene::renderPre3D()
{}

void Indie::OptionsScene::renderPost3D()
{
    context.displayImage(title);
    context.displayImage(wrench);
    context.displayImage(layout);
    back->draw();
    musicVolume->draw();
    soundVolume->draw();
    musicMute->draw();
    soundMute->draw();
}