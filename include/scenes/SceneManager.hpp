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
#include <memory>
#include "IScene.hpp"
#include "ContextManager.hpp"
#include "EventHandler.hpp"
#include "Exceptions.h"

namespace Indie {

class SceneManager {
    public:
        SceneManager();
        ~SceneManager() = default;

        template <typename T>
        T *getScene() {
            for (size_t i = 0; i < scenes.size(); i++) {
                T *scene = dynamic_cast<T*>(scenes[i]);
                if (scene)
                    return (scene);
            }
            throw Exceptions::SceneNotFoundException(ERROR_STR, typeid(T).name(), + " isn't a valid Scene.");
            return NULL;
        }

        template <typename T>
        void addScene(ContextManager &context) {
            IScene *scene = new T(context);
            std::shared_ptr<IScene> smartPtr(scene);

            scenes.push_back(smartPtr);
        }

        void removeScene(size_t id);
        void restartScene(size_t id);
        void restartScenes();
        void setScene(size_t id, ContextManager &context);
        void setSubScene(size_t id);
        void setSceneUpdateActive(bool status);
        void setSubSceneUpdateActive(bool status);
        void setSceneRenderActive(bool status);
        void setSubSceneRenderActive(bool status);
        void update(ContextManager &contextManager, irr::f32 deltaTime);
        std::shared_ptr<IScene> getSceneById(size_t id);

    private:
        std::vector<std::shared_ptr<IScene>> scenes;
        size_t currentScene;
        size_t currentSubScene;
        bool updateScene;
        bool updateSubScene;
        bool renderScene;
        bool renderSubScene;
};

}

#endif /* !SCENEMANAGER_HPP_ */