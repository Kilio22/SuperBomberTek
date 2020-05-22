/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** SceneManager
*/

#include "SceneManager.hpp"

std::vector<IScene*> SceneManager::scenes;
size_t SceneManager::currentScene = 0;
size_t SceneManager::currentSubScene = 0;
bool SceneManager::updateScene = false;
bool SceneManager::renderScene = false;
bool SceneManager::updateSubScene = false;
bool SceneManager::renderSubScene = false;

void SceneManager::removeScene(size_t id)
{
    try {
        if (id >= SceneManager::scenes.size() || id < 0)
            throw (InvalidIndex_("Scene at index " + std::to_string(id) + " doesn't exist."));
        IScene *tmp = SceneManager::scenes[id];
        SceneManager::scenes.erase(SceneManager::scenes.begin() + id);
        delete tmp;
        if (currentScene == id) {
            currentScene = 0;
            SceneManager::setSceneUpdateActive(false);
            SceneManager::setSceneRenderActive(false);
        }
        if (currentSubScene == id) {
            currentSubScene = 0;
            SceneManager::setSubSceneUpdateActive(false);
            SceneManager::setSubSceneRenderActive(false);
        }
    }
    catch (const SceneManagerException& e) {
        std::cerr << e.type() << ": " << e.what() << std::endl;
    }
}

void SceneManager::restartScene(size_t id, ContextManager &context)
{
    try {
        if (id >= SceneManager::scenes.size() || id < 0)
            throw (InvalidIndex_("Scene at index " + std::to_string(id) + " doesn't exist."));
        if (!SceneManager::scenes[id]->reset(context))
            throw (SceneRestartFailed("Scene " + std::to_string(id) + " couldn't be restarted properly. Make sure all the ressources are present in the /ressource folder."));
    }
    catch (const SceneManagerException& e) {
        std::cerr << e.type() << ": " << e.what() << std::endl;
        exit(84);
    }
}

void SceneManager::restartScenes(ContextManager &context)
{
    for (size_t i = 0; i < SceneManager::scenes.size(); i++)
        SceneManager::restartScene(i, context);
}

void SceneManager::setScene(size_t id, ContextManager &context)
{
    context.getSceneManager()->clear();
    try {
        if (id >= SceneManager::scenes.size() || id < 0)
            throw (InvalidIndex_("Scene at index " + std::to_string(id) + " doesn't exist."));
        if (!SceneManager::scenes[id]->reset(context))
            throw (SceneRestartFailed("Scene at index " + std::to_string(id) + " couldn't be initialised properly. Make sure all the ressources are present in the /ressource folder."));
        SceneManager::currentScene = id;
        SceneManager::updateScene = true;
        SceneManager::renderScene = true;
    }
    catch (const SceneManagerException& e) {
        std::cerr << e.type() << ": " << e.what() << std::endl;
    }
}

void SceneManager::setSubScene(size_t id, ContextManager &context)
{
    try {
        if (id >= SceneManager::scenes.size() || id < 0)
            throw (InvalidIndex_("Scene at index " + std::to_string(id) + " doesn't exist."));
        if (!SceneManager::scenes[id]->reset(context))
            throw (SceneRestartFailed("Scene at index " + std::to_string(id) + " couldn't be initialised properly. Make sure all the ressources are present in the /ressource folder."));
        SceneManager::currentSubScene = id;
        SceneManager::updateSubScene = true;
        SceneManager::renderSubScene = true;
    }
    catch (const SceneManagerException& e) {
        std::cerr << e.type() << ": " << e.what() << std::endl;
    }
}

void SceneManager::setSceneUpdateActive(bool status)
{
    SceneManager::updateScene = status;
}

void SceneManager::setSubSceneUpdateActive(bool status)
{
    SceneManager::updateSubScene = status;
}

void SceneManager::setSceneRenderActive(bool status)
{
    SceneManager::renderScene = status;
}

void SceneManager::setSubSceneRenderActive(bool status)
{
    SceneManager::renderSubScene = status;
}

void SceneManager::update(ContextManager &contextManager, irr::f32 deltaTime)
{
        try {
            contextManager.getDriver()->beginScene(true, true, irr::video::SColor(0,0,0,0));

            if (SceneManager::currentScene >= SceneManager::scenes.size() || SceneManager::currentScene < 0)
                throw (InvalidIndex_("Scene at index " + std::to_string(SceneManager::currentScene) + " doesn't exist."));
            if (SceneManager::currentSubScene >= SceneManager::scenes.size() || SceneManager::currentSubScene < 0)
                throw (InvalidIndex_("Scene at index " + std::to_string(SceneManager::currentSubScene) + " doesn't exist."));

            if (SceneManager::updateScene)
                SceneManager::scenes[SceneManager::currentScene]->update(deltaTime);
            if (SceneManager::updateSubScene)
                SceneManager::scenes[SceneManager::currentSubScene]->update(deltaTime);

            if (SceneManager::renderScene)
                SceneManager::scenes[SceneManager::currentScene]->renderPre3D();
            if (SceneManager::renderSubScene)
                SceneManager::scenes[SceneManager::currentSubScene]->renderPre3D();

            contextManager.getSceneManager()->drawAll();

            if (SceneManager::renderScene)
                SceneManager::scenes[SceneManager::currentScene]->renderPost3D();
            if (SceneManager::renderSubScene)
                SceneManager::scenes[SceneManager::currentSubScene]->renderPost3D();

            contextManager.getGuiEnv()->drawAll();
            contextManager.getDriver()->endScene();
        }
        catch (const SceneManagerException& e) {
            std::cerr << e.type() << ": " << e.what() << std::endl;
            exit(84);
        }
}

void SceneManager::drop()
{
    while (SceneManager::scenes.size() > 0)
        SceneManager::removeScene(0);
}