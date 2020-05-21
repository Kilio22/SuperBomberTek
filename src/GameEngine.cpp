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
    SceneManager::setSceneUpdateActive(true);
	SceneManager::setSceneRenderActive(true);
    //SceneManager::setSubScene(1, context);
    //SceneManager::setSubSceneUpdateActive(true);
	//SceneManager::setSubSceneRenderActive(true);
    /* ================================================================================ */
    /* LOOP */
    while (context.getDevice()->run()) {
        MusicManager::update();
        SceneManager::update(context);
    }
    /* ================================================================================ */
    /* MEMORY STUFF */
    MusicManager::drop();
    SceneManager::drop();
    /* ================================================================================ */
}