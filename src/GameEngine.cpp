/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** GameEngine
*/

#include "GameEngine.hpp"
#include "SceneManager.hpp"
#include "Scenes/MenuScene.hpp"
#include "Scenes/TitleScene.hpp"
#include "Scenes/GameScene.hpp"

#include "ServiceLocator.hpp"

static void setupMusicManager()
{
    Indie::ServiceLocator::getInstance().get<Indie::MusicManager>().addMusic("../ressources/musics/main_menu.wav"); // id 0
    Indie::ServiceLocator::getInstance().get<Indie::MusicManager>().addMusic("../ressources/musics/level_select.wav"); // id 1
    Indie::ServiceLocator::getInstance().get<Indie::MusicManager>().mute(); // psk faut pas deconner c'est chiant à la longue
    Indie::ServiceLocator::getInstance().get<Indie::MusicManager>().setMusic(0);
    Indie::ServiceLocator::getInstance().get<Indie::MusicManager>().setVolume(25);
    Indie::ServiceLocator::getInstance().get<Indie::MusicManager>().playMusic();
}

static void setupSceneManager(Indie::ContextManager &context)
{
    Indie::ServiceLocator::getInstance().get<Indie::SceneManager>().addScene<Indie::MenuScene>(context); //id 0
    Indie::ServiceLocator::getInstance().get<Indie::SceneManager>().addScene<Indie::TitleScene>(context); //id 1
    Indie::ServiceLocator::getInstance().get<Indie::SceneManager>().addScene<Indie::GameScene>(context); //id 2
    Indie::ServiceLocator::getInstance().get<Indie::SceneManager>().setScene(2, context);
    Indie::ServiceLocator::getInstance().get<Indie::SceneManager>().setSceneUpdateActive(true);
    Indie::ServiceLocator::getInstance().get<Indie::SceneManager>().setSceneRenderActive(true);
    //Indie::ServiceLocator::getInstance().get<SceneManager>().setSubScene(1, context);
    //Indie::ServiceLocator::getInstance().get<SceneManager>().setSubSceneUpdateActive(true);
    //Indie::ServiceLocator::getInstance().get<SceneManager>().setSubSceneRenderActive(true);
}

void Indie::GameEngine::startGame()
{
    setupMusicManager();
    setupSceneManager(context);
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
            Indie::ServiceLocator::getInstance().get<Indie::MusicManager>().update();
            Indie::ServiceLocator::getInstance().get<SceneManager>().update(context, deltaTime);
        }
        catch (const Indie::Exceptions::IndieException &e) {
            std::cerr << e.getComponent() << ": " << e.what() << std::endl;
            throw (Indie::Exceptions::GameEngineException("GameEngine.cpp line 64", "Update during the game loop failed."));
        }
        lastTime = currentTime;
    }
    /* ================================================================================ */
    /* MEMORY STUFF */
    Indie::ServiceLocator::getInstance().get<Indie::MusicManager>().drop();
    Indie::ServiceLocator::getInstance().get<SceneManager>().drop();
    /* ================================================================================ */
}