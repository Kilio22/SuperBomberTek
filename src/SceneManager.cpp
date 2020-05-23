/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** SceneManager
*/

#include "SceneManager.hpp"

SceneManager::SceneManager() :
scenes(),
currentScene(0),
currentSubScene(0),
updateScene(false),
updateSubScene(false),
renderScene(false),
renderSubScene(false)
{}

IScene *SceneManager::getScene(size_t id)
{
    try {
        if (id >= SceneManager::scenes.size() || id < 0)
            throw (Indie::Exceptions::InvalidIndexException("SceneManager.cpp line 24", "Scene at index " + std::to_string(id) + " doesn't exist."));
    }
    catch (const Indie::Exceptions::IndieException& e) {
        std::cerr << e.getComponent() << ": " << e.what() << std::endl;
        throw (Indie::Exceptions::SceneManagerException("SceneManager.cpp line 28", "Couldn't remove scene " + std::to_string(id) + "."));
    }
    return (scenes[id]);
}

void SceneManager::removeScene(size_t id)
{
    try {
        if (id >= scenes.size() || id < 0)
            throw (Indie::Exceptions::InvalidIndexException("SceneManager.cpp line 37", "Scene at index " + std::to_string(id) + " doesn't exist."));
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
    catch (const Indie::Exceptions::IndieException& e) {
        std::cerr << e.getComponent() << ": " << e.what() << std::endl;
        throw (Indie::Exceptions::SceneManagerException("SceneManager.cpp line 54", "Couldn't remove scene " + std::to_string(id) + "."));
    }
}

void SceneManager::restartScene(size_t id, ContextManager &context)
{
    try {
        if (id >= scenes.size() || id < 0)
            throw (Indie::Exceptions::InvalidIndexException("SceneManager.cpp line 62", "Scene at index " + std::to_string(id) + " doesn't exist."));
        scenes[id]->reset(context);
    }
    catch (const Indie::Exceptions::IndieException& e) {
        std::cerr << e.getComponent() << ": " << e.what() << std::endl;
        throw (Indie::Exceptions::SceneManagerException("SceneManager.cpp line 67", "restartScene failed."));
    }
}

void SceneManager::restartScenes(ContextManager &context)
{
    for (size_t i = 0; i < scenes.size(); i++)
        restartScene(i, context);
}

void SceneManager::setScene(size_t id, ContextManager &context)
{
    context.getSceneManager()->clear();
    try {
        if (id >= scenes.size() || id < 0)
            throw (Indie::Exceptions::InvalidIndexException("SceneManager.cpp line 82", "Scene at index " + std::to_string(id) + " doesn't exist."));
        scenes[id]->reset(context);
        currentScene = id;
        updateScene = true;
        renderScene = true;
    }
    catch (const Indie::Exceptions::IndieException& e) {
        std::cerr << e.getComponent() << ": " << e.what() << std::endl;
        throw (Indie::Exceptions::SceneManagerException("SceneManager.cpp line 90", "setScene failed."));
    }
}

void SceneManager::setSubScene(size_t id, ContextManager &context)
{
    try {
        if (id >= scenes.size() || id < 0)
            throw (Indie::Exceptions::InvalidIndexException("SceneManager.cpp line 98", "Scene at index " + std::to_string(id) + " doesn't exist."));
        scenes[id]->reset(context);
        currentSubScene = id;
        updateSubScene = true;
        renderSubScene = true;
    }
    catch (const Indie::Exceptions::IndieException& e) {
        std::cerr << e.getComponent() << ": " << e.what() << std::endl;
        throw (Indie::Exceptions::SceneManagerException("SceneManager.cpp line 106", "setSubScene failed."));
    }
}

void SceneManager::setSceneUpdateActive(bool status)
{
    updateScene = status;
}

void SceneManager::setSubSceneUpdateActive(bool status)
{
    updateSubScene = status;
}

void SceneManager::setSceneRenderActive(bool status)
{
    renderScene = status;
}

void SceneManager::setSubSceneRenderActive(bool status)
{
    renderSubScene = status;
}

void SceneManager::update(ContextManager &contextManager, irr::f32 deltaTime)
{
        try {
            contextManager.getDriver()->beginScene(true, true, irr::video::SColor(0,0,0,0));

            if (currentScene >= scenes.size() || currentScene < 0)
                throw (Indie::Exceptions::InvalidIndexException("SceneManager.cpp line 135", "Scene at index " + std::to_string(currentScene) + " doesn't exist."));
            if (currentSubScene >= scenes.size() || currentSubScene < 0)
                throw (Indie::Exceptions::InvalidIndexException("SceneManager.cpp line 138", "Scene at index " + std::to_string(currentSubScene) + " doesn't exist."));

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
        catch (const Indie::Exceptions::IndieException& e) {
        std::cerr << e.getComponent() << ": " << e.what() << std::endl;
        throw (Indie::Exceptions::SceneManagerException("SceneManager.cpp line 162", "update failed."));
    }
}

void SceneManager::drop()
{
    while (scenes.size() > 0)
        removeScene(0);
}