/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** SceneManager
*/

#include "SceneManager.hpp"

Indie::SceneManager::SceneManager()
    : scenes()
    , currentScene(0)
    , currentSubScene(0)
    , updateScene(false)
    , updateSubScene(false)
    , renderScene(false)
    , renderSubScene(false)
{
}

Indie::IScene *Indie::SceneManager::getScene(size_t id)
{
    if (id >= scenes.size() || id < 0)
        throw Indie::Exceptions::InvalidIndexException(ERROR_STR, "Scene at index " + std::to_string(id) + " doesn't exist.");
    return (scenes[id]);
}

void Indie::SceneManager::removeScene(size_t id)
{
    if (id >= scenes.size() || id < 0)
        throw Indie::Exceptions::InvalidIndexException(ERROR_STR, "Scene at index " + std::to_string(id) + " doesn't exist.");
    IScene *tmp = scenes[id];
    scenes.erase(scenes.begin() + id);
    delete tmp;
    if (currentScene == id) {
        currentScene = 0;
        setSceneUpdateActive(false);
        setSceneRenderActive(false);
    }
    if (currentSubScene == id) {
        currentSubScene = 0;
        setSubSceneUpdateActive(false);
        setSubSceneRenderActive(false);
    }
}

void Indie::SceneManager::restartScene(size_t id, ContextManager &context)
{
    if (id >= scenes.size() || id < 0)
        throw (Indie::Exceptions::InvalidIndexException(ERROR_STR, "Scene at index " + std::to_string(id) + " doesn't exist."));
    scenes[id]->reset(context);
}

void Indie::SceneManager::restartScenes(ContextManager &context)
{
    for (size_t i = 0; i < scenes.size(); i++)
        restartScene(i, context);
}

void Indie::SceneManager::setScene(size_t id, ContextManager &context)
{
    context.getSceneManager()->clear();
    if (id >= scenes.size() || id < 0)
        throw (Indie::Exceptions::InvalidIndexException(ERROR_STR, "Scene at index " + std::to_string(id) + " doesn't exist."));
    scenes[id]->reset(context);
    currentScene = id;
    updateScene = true;
    renderScene = true;
}

void Indie::SceneManager::setSubScene(size_t id, ContextManager &context)
{
    if (id >= scenes.size() || id < 0)
        throw (Indie::Exceptions::InvalidIndexException(ERROR_STR, "Scene at index " + std::to_string(id) + " doesn't exist."));
    scenes[id]->reset(context);
    currentSubScene = id;
    updateSubScene = true;
    renderSubScene = true;
}

void Indie::SceneManager::setSceneUpdateActive(bool status)
{
    updateScene = status;
}

void Indie::SceneManager::setSubSceneUpdateActive(bool status)
{
    updateSubScene = status;
}

void Indie::SceneManager::setSceneRenderActive(bool status)
{
    renderScene = status;
}

void Indie::SceneManager::setSubSceneRenderActive(bool status)
{
    renderSubScene = status;
}

void Indie::SceneManager::update(ContextManager &contextManager, irr::f32 deltaTime)
{
    contextManager.getDriver()->beginScene(true, true, irr::video::SColor(0,0,0,0));

    if (currentScene >= scenes.size() || currentScene < 0)
        throw (Indie::Exceptions::InvalidIndexException(ERROR_STR, "Scene at index " + std::to_string(currentScene) + " doesn't exist."));
    if (currentSubScene >= scenes.size() || currentSubScene < 0)
        throw (Indie::Exceptions::InvalidIndexException(ERROR_STR, "Scene at index " + std::to_string(currentSubScene) + " doesn't exist."));

    if (updateScene)
        scenes[currentScene]->update(deltaTime);
    if (updateSubScene)
        scenes[currentSubScene]->update(deltaTime);

    if (renderScene)
        scenes[currentScene]->renderPre3D();
    if (renderSubScene)
        scenes[currentSubScene]->renderPre3D();

    contextManager.getSceneManager()->drawAll();

    if (renderScene)
        scenes[currentScene]->renderPost3D();
    if (renderSubScene)
        scenes[currentSubScene]->renderPost3D();

    contextManager.getGuiEnv()->drawAll();
    contextManager.getDriver()->endScene();
}

void Indie::SceneManager::drop()
{
    while (scenes.size() > 0)
        removeScene(0);
}