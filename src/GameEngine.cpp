/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** GameEngine
*/

#include "GameEngine.hpp"
#include "Scenes.hpp"
#include "SceneManager.hpp"
#include "ServiceLocator.hpp"

void Indie::GameEngine::setupMusicManager()
{
    ServiceLocator::getInstance().get<MusicManager>().addMusic("../ressources/musics/main_menu.wav"); // id 0
    ServiceLocator::getInstance().get<MusicManager>().addMusic("../ressources/musics/level_select.wav"); // id 1
    ServiceLocator::getInstance().get<MusicManager>().mute(); // psk faut pas deconner c'est chiant à la longue
    ServiceLocator::getInstance().get<MusicManager>().setMusic(0);
    ServiceLocator::getInstance().get<MusicManager>().setVolume(5);
    ServiceLocator::getInstance().get<MusicManager>().playMusic();
}

void Indie::GameEngine::setupSceneManager(ContextManager &context)
{
    ServiceLocator::getInstance().get<SceneManager>().addScene<SplashScene>(context); //id 0
    ServiceLocator::getInstance().get<SceneManager>().addScene<MenuScene>(context); //id 1
    ServiceLocator::getInstance().get<SceneManager>().addScene<TitleScene>(context); //id 2
    ServiceLocator::getInstance().get<SceneManager>().addScene<MainMenuScene>(context); //id 3
    ServiceLocator::getInstance().get<SceneManager>().addScene<GameScene>(context); //id 4
    ServiceLocator::getInstance().get<SceneManager>().addScene<PauseScene>(context); //id 4
    ServiceLocator::getInstance().get<SceneManager>().setScene<SplashScene>(context);
    ServiceLocator::getInstance().get<SceneManager>().setSceneUpdateActive(true);
    ServiceLocator::getInstance().get<SceneManager>().setSceneRenderActive(true);
    // ServiceLocator::getInstance().get<SceneManager>().setSubScene(2);
    // ServiceLocator::getInstance().get<SceneManager>().setSubSceneUpdateActive(true);
    // ServiceLocator::getInstance().get<SceneManager>().setSubSceneRenderActive(true);
}

Indie::GameEngine::GameEngine()
    : context(ServiceLocator::getInstance().get<ContextManager>())
{
}

void Indie::GameEngine::startGame()
{
    this->setupMusicManager();
    this->setupSceneManager(context);
    this->context.getDevice()->setEventReceiver(&EventHandler::getInstance());
    /* ================================================================================ */
    /* LOOP */
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
        // std::cout << "Delta time: " << deltaTime << ", FPS: " << this->context.getDriver()->getFPS() << std::endl;
        if (totalDeltaTime >= 0.016f) {
            ServiceLocator::getInstance().get<MusicManager>().update();
            ServiceLocator::getInstance().get<SceneManager>().update(context, totalDeltaTime);
            totalDeltaTime = 0.f;
        }
        lastTime = currentTime;
    }
    /* ================================================================================ */
    /* MEMORY STUFF */
    /* ================================================================================ */
}