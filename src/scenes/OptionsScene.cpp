/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** OptionsScene
*/

#include "OptionsScene.hpp"
#include "ImageLoader.hpp"
#include "MainMenuScene.hpp"
#include "MusicManager.hpp"
#include "SceneManager.hpp"
#include "ServiceLocator.hpp"
#include "SoundManager.hpp"

Indie::OptionsScene::OptionsScene(Indie::ContextManager &context)
    : context(context)
    , selector(3, 5, irr::EKEY_CODE::KEY_UP, irr::EKEY_CODE::KEY_DOWN, irr::EKEY_CODE::KEY_LEFT, irr::EKEY_CODE::KEY_RIGHT)
    , musicVolumeSelector(21, 1, irr::EKEY_CODE::KEY_UP, irr::EKEY_CODE::KEY_DOWN, irr::EKEY_CODE::KEY_LEFT, irr::EKEY_CODE::KEY_RIGHT, true, false)
    , soundVolumeSelector(21, 1, irr::EKEY_CODE::KEY_UP, irr::EKEY_CODE::KEY_DOWN, irr::EKEY_CODE::KEY_LEFT, irr::EKEY_CODE::KEY_RIGHT, true, false)
    , back(std::make_unique<Button>(context))
    , musicVolume(std::make_unique<Button>(context, false))
    , soundVolume(std::make_unique<Button>(context, false))
    , musicMute(std::make_unique<Checkbox>(context))
    , soundMute(std::make_unique<Checkbox>(context))
{
    selector.setPos(1, 0);
    musicVolumeSelector.setPos(20, 0);
    soundVolumeSelector.setPos(20, 0);
}

void Indie::OptionsScene::init()
{
    title = Indie::ServiceLocator::getInstance().get<Indie::ImageLoader>().getImage("../ressources/images/options/title.png");
    wrench = Indie::ServiceLocator::getInstance().get<Indie::ImageLoader>().getImage("../ressources/images/options/drawing.png");
    layout = Indie::ServiceLocator::getInstance().get<Indie::ImageLoader>().getImage("../ressources/images/options/Layout.png");

    font = context.getGuiEnv()->getFont("../ressources/font/Banschrift.xml");
    if (font == nullptr) {
        throw Indie::Exceptions::FileNotFoundException(ERROR_STR, "Cannot open file: \"../ressources/font/Banschrift.xml\"");
    }
    musicVolume->init(context, "../ressources/images/options/Vol2.png", 1, 0, POS(0, 0));
    musicMute->init("../ressources/images/options/Check2.png", 1, 1, POS(0, 0));
    soundVolume->init(context, "../ressources/images/options/Vol1.png", 1, 2, POS(0, 0));
    soundMute->init("../ressources/images/options/Check1.png", 1, 3, POS(0, 0));
    back->init(context, "../ressources/images/options/Retour.png", 1, 4, POS(0, 0));

    musicMute->setStatus(Indie::ServiceLocator::getInstance().get<Indie::MusicManager>().isMusicMuted());
    soundMute->setStatus(Indie::ServiceLocator::getInstance().get<Indie::SoundManager>().isMuted());
    musicVolumeSelector.setPos((int)Indie::ServiceLocator::getInstance().get<Indie::MusicManager>().getMusicVolume(), 0);
    soundVolumeSelector.setPos((int)Indie::ServiceLocator::getInstance().get<Indie::SoundManager>().getVolume(), 0);
}

void Indie::OptionsScene::reset()
{
    selector.setPos(0, 0);
    init();
}

void Indie::OptionsScene::update(irr::f32 ticks)
{
    selector.update();
    if (selector.getPos().first != 1) {
        if (selector.getPos().second == 1 || selector.getPos().second == 3)
            ServiceLocator::getInstance().get<SoundManager>().playSound("menu_lock");
        selector.setPos(1, selector.getPos().second);
    }
    back->update(selector.getPos());
    musicVolume->update(selector.getPos());
    soundVolume->update(selector.getPos());
    musicMute->update(selector.getPos());
    soundMute->update(selector.getPos());
    if (back->getStatus() == Button::Status::Pressed || Indie::EventHandler::getInstance().isKeyPressed(irr::KEY_ESCAPE) == true) {
        ServiceLocator::getInstance().get<Indie::SceneManager>().setSubScene<Indie::MainMenuScene>();
        skipScene(true, true, true, true);
        EventHandler::getInstance().resetKeys();
    }
    if (musicMute->getStatus()) {
        Indie::ServiceLocator::getInstance().get<Indie::MusicManager>().mute();
    } else {
        Indie::ServiceLocator::getInstance().get<Indie::MusicManager>().unMute();
    }
    Indie::ServiceLocator::getInstance().get<Indie::SoundManager>().setMute(soundMute->getStatus());
    if (musicVolume->getStatus() == Button::Status::Selected) {
        musicVolumeSelector.update();
    }
    if (soundVolume->getStatus() == Button::Status::Selected) {
        soundVolumeSelector.update();
    }
    Indie::ServiceLocator::getInstance().get<Indie::SoundManager>().setVolume(soundVolumeSelector.getPos().first);
    Indie::ServiceLocator::getInstance().get<Indie::MusicManager>().setVolume(musicVolumeSelector.getPos().first);
}

void Indie::OptionsScene::renderPre3D() {}

void Indie::OptionsScene::renderPost3D()
{
    irr::core::stringw musicVol = L"";
    irr::core::stringw soundVol = L"";

    musicVol += irr::core::stringw(musicVolumeSelector.getPos().first * 5);
    soundVol += irr::core::stringw(soundVolumeSelector.getPos().first * 5);

    context.displayImage(title);
    context.displayImage(wrench);
    context.displayImage(layout);
    back->draw();
    musicVolume->draw();
    soundVolume->draw();
    musicMute->draw();
    soundMute->draw();
    font->draw(musicVol.c_str(), irr::core::rect<irr::s32>(1175 - (8 * (musicVol.size() - 1)), 218, 0, 0), irr::video::SColor(255, 255, 255, 255));
    font->draw(soundVol.c_str(), irr::core::rect<irr::s32>(1175 - (8 * (soundVol.size() - 1)), 395, 0, 0), irr::video::SColor(255, 255, 255, 255));
}

void Indie::OptionsScene::skipScene(bool update, bool render, bool subUpdate, bool subRender)
{
    Indie::ServiceLocator::getInstance().get<SceneManager>().setSceneUpdateActive(update);
    Indie::ServiceLocator::getInstance().get<SceneManager>().setSceneRenderActive(render);
    Indie::ServiceLocator::getInstance().get<SceneManager>().setSubSceneUpdateActive(subUpdate);
    Indie::ServiceLocator::getInstance().get<SceneManager>().setSubSceneRenderActive(subRender);
}