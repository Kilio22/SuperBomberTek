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
#include "Exceptions.h"

namespace Indie {

class SceneManager {
    public:
        SceneManager();
        ~SceneManager() = default;

        template <typename T>
        void addScene(ContextManager &context) {
            IScene *scene = new T;

            scenes.push_back(scene);
        }
        void removeScene(size_t id);
        void restartScene(size_t id, ContextManager &context);
        void restartScenes(ContextManager &context);
        void setScene(size_t id, ContextManager &context);
        void setSubScene(size_t id, ContextManager &context);
        void setSceneUpdateActive(bool status);
        void setSubSceneUpdateActive(bool status);
        void setSceneRenderActive(bool status);
        void setSubSceneRenderActive(bool status);
        void update(ContextManager &contextManager, irr::f32 deltaTime);
        void drop();
        IScene *getScene(size_t id);

    private:
        std::vector<IScene *> scenes;
        size_t currentScene;
        size_t currentSubScene;
        bool updateScene;
        bool updateSubScene;
        bool renderScene;
        bool renderSubScene;
};

}

#endif /* !SCENEMANAGER_HPP_ */