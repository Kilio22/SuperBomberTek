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

void GameEngine::startGame()
{
    /* ================================================================================ */
    /* MUSIC MANAGER STUFF */
    MusicManager::AddMusic("../ressources/musics/main_menu.wav"); // id 0
    MusicManager::AddMusic("../ressources/musics/level_select.wav"); // id 1
    //MusicManager::mute(); // psk faut pas deconner c'est chiant à la longue
    MusicManager::setMusic(0);
    MusicManager::setVolume(25);
    MusicManager::playMusic();
    /* ================================================================================ */
    /* SCENE MANAGER STUFF */
    SceneManager::AddScene<MenuScene>(context); //id 0
    SceneManager::AddScene<TitleScene>(context); //id 1
    SceneManager::AddScene<GameScene>(context); //id 2
    SceneManager::setScene(2, context);
    // SceneManager::setSceneUpdateActive(true);
    // SceneManager::setSceneRenderActive(true);
    //SceneManager::setSubScene(1, context);
    //SceneManager::setSubSceneUpdateActive(true);
    //SceneManager::setSubSceneRenderActive(true);
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
        MusicManager::update();
        SceneManager::update(context, deltaTime);
        lastTime = currentTime;
    }
    /* ================================================================================ */
    /* MEMORY STUFF */
    MusicManager::drop();
    SceneManager::drop();
    /* ================================================================================ */
}