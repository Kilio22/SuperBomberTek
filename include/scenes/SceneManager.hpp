/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** SceneManager
*/

#ifndef SCENEMANAGER_HPP_
#define SCENEMANAGER_HPP_

#include "ContextManager.hpp"
#include "EventHandler.hpp"
#include "Exceptions.h"
#include "IScene.hpp"
#include "TypeIndex.hpp"
#include <memory>
#include <unordered_map>

namespace Indie
{
    class SceneManager
    {
    public:
        SceneManager();
        ~SceneManager();

        template <typename T>
        T *getScene()
        {
            auto found = this->scenes.find(getTypeIndex<T>());

            if (found != this->scenes.end()) {
                return reinterpret_cast<T *>(found->second.get());
            }
            return nullptr;
        }

        template <typename T>
        void addScene(ContextManager &context)
        {
            auto ptr = std::make_unique<T>(context);

            scenes.insert({ getTypeIndex<T>(), std::move(ptr) });
        }

        // template <typename T>
        // void removeScene()
        // {
        // }

        template <typename T>
        void restartScene()
        {
            auto index = getTypeIndex<T>();

            if (scenes.count(index) == 0)
                throw Exceptions::SceneManagerException(ERROR_STR, "Scene " + std::string(index.name()) + "does not exist.");
            scenes[index]->reset();
        }

        void restartScenes();

        template <typename T>
        void setScene(ContextManager &context)
        {
            auto index = getTypeIndex<T>();

            // Ecran de chargement quand ça load une scène mais c'est chelou un peu
            //context.displayImage(loading);
            //context.getDriver()->endScene();
            //context.getDriver()->beginScene(true, true, irr::video::SColor(0,0,0,0));
            if (scenes.count(index) == 0)
                throw Exceptions::SceneManagerException(ERROR_STR, "Scene " + std::string(index.name()) + "does not exist.");
            EventHandler::getInstance().resetKeys();
            context.getSceneManager()->clear();
            this->restartScene<T>();
            currentScene = index;
            updateScene = true;
            renderScene = true;
        }

        template <typename T>
        void setSubScene()
        {
            auto index = getTypeIndex<T>();

            //context->displayImage(loading);
            //context->getDriver()->endScene();
            //context->getDriver()->beginScene(true, true, irr::video::SColor(0,0,0,0));
            if (scenes.count(index) == 0)
                throw Exceptions::SceneManagerException(ERROR_STR, "Scene " + std::string(index.name()) + "does not exist.");
            EventHandler::getInstance().resetKeys();
            this->restartScene<T>();
            currentSubScene = index;
            updateSubScene = true;
            renderSubScene = true;
        }

        void setSceneUpdateActive(bool status);
        void setSubSceneUpdateActive(bool status);
        void setSceneRenderActive(bool status);
        void setSubSceneRenderActive(bool status);
        void update(ContextManager &contextManager, irr::f32 deltaTime);
        void initLoading(ContextManager *context);

    private:
        std::unordered_map<TypeIndex, std::unique_ptr<IScene>> scenes;
        TypeIndex currentScene;
        TypeIndex currentSubScene;
        bool updateScene;
        bool updateSubScene;
        bool renderScene;
        bool renderSubScene;
        Image *loading;
        ContextManager *context;
    };

}

#endif /* !SCENEMANAGER_HPP_ */