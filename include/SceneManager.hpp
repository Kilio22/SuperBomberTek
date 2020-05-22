/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** SceneManager
*/

#ifndef SCENEMANAGER_HPP_
#define SCENEMANAGER_HPP_

#include <iostream>
#include <string>
#include <vector>
#include "IScene.hpp"
#include "ContextManager.hpp"

class SceneManagerException : public std::exception
{
    public:
        SceneManagerException(std::string const &message, std::string const type) noexcept {
            _message = message;
            _type = type;
        }

        const char *type() const noexcept {
            return (_type.data());
        }
        const char *what() const noexcept override {
            return (_message.data());
        };
    protected:
        std::string _message;
        std::string _type;
};

class InvalidIndex_ : public SceneManagerException
{
    public:
        InvalidIndex_(std::string const &message) noexcept : SceneManagerException(message, "InvalidIndex")
        {}
};

class SceneInitFailed : public SceneManagerException
{
    public:
        SceneInitFailed(std::string const &message) noexcept : SceneManagerException(message, "SceneInitFailed")
        {}
};

class SceneRestartFailed : public SceneManagerException
{
    public:
        SceneRestartFailed(std::string const &message) noexcept : SceneManagerException(message, "SceneRestartFailed")
        {}
};

class SceneManager {
    public:
        SceneManager() = delete;
        ~SceneManager() = delete;

    template <typename T>
    static void AddScene(ContextManager &context) {
        IScene *scene = new T;

        SceneManager::scenes.push_back(scene);
    }
    static void removeScene(size_t id);
    static void restartScene(size_t id, ContextManager &context);
    static void restartScenes(ContextManager &context);

    static void setScene(size_t id, ContextManager &context);
    static void setSubScene(size_t id, ContextManager &context);

    static void setSceneUpdateActive(bool status);
    static void setSubSceneUpdateActive(bool status);
    static void setSceneRenderActive(bool status);
    static void setSubSceneRenderActive(bool status);
    static void update(ContextManager &contextManager, irr::f32 deltaTime);

    static void drop();

    static std::vector<IScene*> scenes;
    static size_t currentScene;
    static size_t currentSubScene;
    static bool updateScene;
    static bool renderScene;
    static bool updateSubScene;
    static bool renderSubScene;
};

#endif /* !SCENEMANAGER_HPP_ */