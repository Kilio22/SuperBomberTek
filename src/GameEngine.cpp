/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** GameEngine
*/

#include "GameEngine.hpp"
#include "InitGame.hpp"
#include "SaveManager.hpp"
#include "SceneManager.hpp"
#include "Scenes.h"
#include "ServiceLocator.hpp"
#include <fstream>
#include <iostream>

void Indie::GameEngine::setupMusicManager()
{
    ServiceLocator::getInstance().get<MusicManager>().addMusic("../ressources/musics/main_menu.wav"); // id 0
    ServiceLocator::getInstance().get<MusicManager>().addMusic("../ressources/musics/level_select.wav"); // id 1
    ServiceLocator::getInstance().get<MusicManager>().setMusic(0);
}

void Indie::GameEngine::setupSoundManager()
{
    ServiceLocator::getInstance().get<SoundManager>().addSound("../ressources/sounds/bad.wav");
    ServiceLocator::getInstance().get<SoundManager>().addSound("../ressources/sounds/bomb_drop.wav");
    ServiceLocator::getInstance().get<SoundManager>().addSound("../ressources/sounds/bomb_explode.wav");
    ServiceLocator::getInstance().get<SoundManager>().addSound("../ressources/sounds/die.wav");
    ServiceLocator::getInstance().get<SoundManager>().addSound("../ressources/sounds/level_up.wav");
    ServiceLocator::getInstance().get<SoundManager>().addSound("../ressources/sounds/menu_back.wav");
    ServiceLocator::getInstance().get<SoundManager>().addSound("../ressources/sounds/menu_lock.wav");
    ServiceLocator::getInstance().get<SoundManager>().addSound("../ressources/sounds/menu_move.wav");
    ServiceLocator::getInstance().get<SoundManager>().addSound("../ressources/sounds/menu_select.wav");
    ServiceLocator::getInstance().get<SoundManager>().addSound("../ressources/sounds/power_down.wav");
    ServiceLocator::getInstance().get<SoundManager>().addSound("../ressources/sounds/power_up.wav");
    ServiceLocator::getInstance().get<SoundManager>().addSound("../ressources/sounds/title_select.wav");
    ServiceLocator::getInstance().get<SoundManager>().addSound("../ressources/sounds/xp_up.wav");
}

void Indie::GameEngine::setupSceneManager(ContextManager &context)
{
    ServiceLocator::getInstance().get<SceneManager>().initLoading(&context);
    ServiceLocator::getInstance().get<SceneManager>().addScene<SplashScene>(context);
    ServiceLocator::getInstance().get<SceneManager>().addScene<MenuScene>(context);
    ServiceLocator::getInstance().get<SceneManager>().addScene<TitleScene>(context);
    ServiceLocator::getInstance().get<SceneManager>().addScene<MainMenuScene>(context);
    ServiceLocator::getInstance().get<SceneManager>().addScene<GameScene>(context);
    ServiceLocator::getInstance().get<SceneManager>().addScene<PauseScene>(context);
    ServiceLocator::getInstance().get<SceneManager>().addScene<OptionsScene>(context);
    ServiceLocator::getInstance().get<SceneManager>().addScene<IntroScene>(context);
    ServiceLocator::getInstance().get<SceneManager>().addScene<SoloScene>(context);
    ServiceLocator::getInstance().get<SceneManager>().addScene<EndScene>(context);
    ServiceLocator::getInstance().get<SceneManager>().addScene<MultiScene>(context);
    ServiceLocator::getInstance().get<SceneManager>().addScene<MultiKeybindsScene>(context);
    ServiceLocator::getInstance().get<SceneManager>().setScene<SplashScene>(context);
    ServiceLocator::getInstance().get<SceneManager>().setSceneUpdateActive(true);
    ServiceLocator::getInstance().get<SceneManager>().setSceneRenderActive(true);
}

Indie::GameEngine::GameEngine()
    : context(ServiceLocator::getInstance().get<ContextManager>())
{
    loadImage = context.getDriver()->getTexture("../ressources/images/Loading.png");
}

Indie::GameEngine::~GameEngine()
{
    if (loadImage)
        context.getDriver()->removeTexture(loadImage);
}

void Indie::GameEngine::gameLoop(void)
{
    irr::u32 lastTime = this->context.getDevice()->getTimer()->getTime();
    irr::u32 currentTime = 0;
    irr::f32 deltaTime = 0;
    irr::f32 totalDeltaTime = 0;

    while (context.getDevice()->run()) {
        currentTime = this->context.getDevice()->getTimer()->getTime();
        deltaTime = (irr::f32)((currentTime - lastTime) / 1000.f);
        totalDeltaTime += deltaTime;
        // std::cout << "Delta time: " << deltaTime << ", FPS: " << this->context.getDriver()->getFPS() << std::endl;
        if (totalDeltaTime >= 0.016f) { // limit framerate
            ServiceLocator::getInstance().get<MusicManager>().update();
            ServiceLocator::getInstance().get<SoundManager>().update();
            ServiceLocator::getInstance().get<SceneManager>().update(context, totalDeltaTime);
            totalDeltaTime = 0.f;
            EventHandler::getInstance().resetKeysReleased();
            EventHandler::getInstance().resetKeysStatusOnce();
        }
        lastTime = currentTime;
    }
}

void Indie::GameEngine::startGame()
{
    /* LOADING SCREEN */
    context.getDriver()->beginScene(true, true, irr::video::SColor(0, 0, 0, 0));
    context.displayImage(loadImage);
    context.getDriver()->endScene();

    ServiceLocator::getInstance().get<ImageLoader>();

    this->setupSoundManager();
    this->setupMusicManager();
    this->setupSceneManager(context);

    ServiceLocator::getInstance().get<SaveManager>().loadSave("../ressources/.saves/default.txt");
    ServiceLocator::getInstance().get<MusicManager>().playMusic();

    this->context.getDevice()->setEventReceiver(&EventHandler::getInstance());

    this->context.getDevice()->getTimer()->stop();
    this->context.getDevice()->getTimer()->start();

    this->gameLoop();
}