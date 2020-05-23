/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** GameEngine
*/

#include "GameEngine.hpp"

#include "Scenes/MenuScene.hpp"
#include "Scenes/TitleScene.hpp"
#include "Scenes/GameScene.hpp"

#include "ServiceLocator.hpp"

static void setupMusicManager()
{
    ServiceLocator::musicManager.addMusic("../ressources/musics/main_menu.wav"); // id 0
    ServiceLocator::musicManager.addMusic("../ressources/musics/level_select.wav"); // id 1
    ServiceLocator::musicManager.mute(); // psk faut pas deconner c'est chiant à la longue
    ServiceLocator::musicManager.setMusic(0);
    ServiceLocator::musicManager.setVolume(25);
    ServiceLocator::musicManager.playMusic();
}

static void setupSceneManager(ContextManager &context)
{
    ServiceLocator::sceneManager.addScene<MenuScene>(context); //id 0
    ServiceLocator::sceneManager.addScene<TitleScene>(context); //id 1
    ServiceLocator::sceneManager.addScene<GameScene>(context); //id 2
    ServiceLocator::sceneManager.setScene(0, context);
    ServiceLocator::sceneManager.setSceneUpdateActive(true);
    ServiceLocator::sceneManager.setSceneRenderActive(true);
    ServiceLocator::sceneManager.setSubScene(1, context);
    ServiceLocator::sceneManager.setSubSceneUpdateActive(true);
    ServiceLocator::sceneManager.setSubSceneRenderActive(true);
}

void GameEngine::startGame()
{
    try {
        setupMusicManager();
        setupSceneManager(context);
    }
    catch (const Indie::Exceptions::IndieException &e) {
        std::cerr << e.getComponent() << ": " << e.what() << std::endl;
        throw (Indie::Exceptions::GameEngineException("GameEngine.cpp line 46", "Setup failed."));
    }
    /* ================================================================================ */
    /* LOOP */
    this->context.getDevice()->getTimer()->stop();
    this->context.getDevice()->getTimer()->start();

    irr::u32 lastTime = this->context.getDevice()->getTimer()->getTime();
    irr::u32 currentTime = 0;
    irr::f32 deltaTime = 0;
    while (context.getDevice()->run()) {
        currentTime = this->context.getDevice()->getTimer()->getTime();
        deltaTime = (irr::f32)(currentTime - lastTime) / 1000.f;
        try {
            ServiceLocator::musicManager.update();
            ServiceLocator::sceneManager.update(context, deltaTime);
        }
        catch (const Indie::Exceptions::IndieException &e) {
            std::cerr << e.getComponent() << ": " << e.what() << std::endl;
            throw (Indie::Exceptions::GameEngineException("GameEngine.cpp line 64", "Update during the game loop failed."));
        }
        lastTime = currentTime;
    }
    /* ================================================================================ */
    /* MEMORY STUFF */
    ServiceLocator::musicManager.drop();
    ServiceLocator::sceneManager.drop();
    /* ================================================================================ */
}