/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** SceneManager
*/

#include "SceneManager.hpp"
#include <algorithm>

Indie::SceneManager::SceneManager()
    : scenes()
    , currentScene(getTypeIndex<SceneManager>())
    , currentSubScene(getTypeIndex<SceneManager>())
    , updateScene(false)
    , updateSubScene(false)
    , renderScene(false)
    , renderSubScene(false)
{
}

Indie::SceneManager::~SceneManager()
{
    if (loading)
        context->getDriver()->removeTexture(loading);
}

void Indie::SceneManager::initLoading(Indie::ContextManager *context)
{
    this->context = context;
    loading = context->getDriver()->getTexture("../ressources/images/Loading.png");
}

// std::shared_ptr<Indie::IScene> Indie::SceneManager::getSceneById(size_t id)
// {
//     if (id >= scenes.size())
//         throw Indie::Exceptions::InvalidIndexException(ERROR_STR, "Scene at index " + std::to_string(id) + " doesn't exist.");
//     return (scenes[id]);
// }

// void Indie::SceneManager::removeScene(size_t id)
// {
//     if (id >= scenes.size())
//         throw Indie::Exceptions::InvalidIndexException(ERROR_STR, "Scene at index " + std::to_string(id) + " doesn't exist.");
//     std::shared_ptr<Indie::IScene> tmp = scenes[id];
//     scenes.erase(scenes.begin() + id);
//     if (currentScene == id) {
//         currentScene = 0;
//         setSceneUpdateActive(false);
//         setSceneRenderActive(false);
//     }
//     if (currentSubScene == id) {
//         currentSubScene = 0;
//         setSubSceneUpdateActive(false);
//         setSubSceneRenderActive(false);
//     }
// }

// void Indie::SceneManager::restartScene(size_t id)
// {
//     if (id >= scenes.size())
//         throw (Indie::Exceptions::InvalidIndexException(ERROR_STR, "Scene at index " + std::to_string(id) + " doesn't exist."));
//     scenes[id]->reset();
// }

void Indie::SceneManager::restartScenes()
{
    std::for_each(this->scenes.begin(), this->scenes.end(), [](auto &ptr) { ptr.second->reset(); });
}

// void Indie::SceneManager::setScene(size_t id, ContextManager &context)
// {
//     EventHandler::getInstance().resetKeys();
//     context.getSceneManager()->clear();
//     if (id >= scenes.size())
//         throw (Indie::Exceptions::InvalidIndexException(ERROR_STR, "Scene at index " + std::to_string(id) + " doesn't exist."));
//     scenes[id]->reset();
//     currentScene = id;
//     updateScene = true;
//     renderScene = true;
// }

// void Indie::SceneManager::setSubScene(size_t id)
// {
//     EventHandler::getInstance().resetKeys();
//     if (id >= scenes.size())
//         throw (Indie::Exceptions::InvalidIndexException(ERROR_STR, "Scene at index " + std::to_string(id) + " doesn't exist."));
//     scenes[id]->reset();
//     currentSubScene = id;
//     updateSubScene = true;
//     renderSubScene = true;
// }

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
    contextManager.getDriver()->beginScene(true, true, irr::video::SColor(0, 0, 0, 0));

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
