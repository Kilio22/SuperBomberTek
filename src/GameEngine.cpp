/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** GameEngine
*/

#include "GameEngine.hpp"
#include "InitGame.hpp"
#include "SceneManager.hpp"
#include "Scenes.hpp"
#include "ServiceLocator.hpp"

void Indie::GameEngine::setupMusicManager()
{
    ServiceLocator::getInstance().get<MusicManager>().addMusic("../ressources/musics/main_menu.wav"); // id 0
    ServiceLocator::getInstance().get<MusicManager>().addMusic("../ressources/musics/level_select.wav"); // id 1
    ServiceLocator::getInstance().get<MusicManager>().setMusic(0);
    ServiceLocator::getInstance().get<MusicManager>().mute(); // J'en ai marre d'entendre cette merde à chaque fois que je lance
    ServiceLocator::getInstance().get<MusicManager>().setVolume(25);
    ServiceLocator::getInstance().get<MusicManager>().playMusic();
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

void Indie::GameEngine::startGame()
{
    /* ================================================================================ */
    /* LOADING SCREEN */
    /* ================================================================================ */
    context.getDriver()->beginScene(true, true, irr::video::SColor(0, 0, 0, 0));
    context.displayImage(loadImage);
    context.getDriver()->endScene();
    ServiceLocator::getInstance().get<ImageLoader>();
    this->setupMusicManager();
    this->setupSceneManager(context);
    /* ================================================================================ */
    /* LOOP */
    /* ================================================================================ */
    this->context.getDevice()->setEventReceiver(&EventHandler::getInstance());
    this->context.getDevice()->getTimer()->stop();
    this->context.getDevice()->getTimer()->start();

    irr::u32 lastTime = this->context.getDevice()->getTimer()->getTime();
    irr::u32 currentTime = 0;
    irr::f32 deltaTime = 0;
    irr::f32 totalDeltaTime = 0;
    while (context.getDevice()->run()) {
        currentTime = this->context.getDevice()->getTimer()->getTime();
        deltaTime = (irr::f32)((currentTime - lastTime) / 1000.f);
        totalDeltaTime += deltaTime;
        //std::cout << "Delta time: " << deltaTime << ", FPS: " << this->context.getDriver()->getFPS() << std::endl;
        if (totalDeltaTime >= 0.016f) {
            ServiceLocator::getInstance().get<MusicManager>().update();
            ServiceLocator::getInstance().get<SceneManager>().update(context, totalDeltaTime);
            totalDeltaTime = 0.f;
        }
        lastTime = currentTime;
    }
}