/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** GameEngine
*/

#ifndef GAMEENGINE_HPP_
#define GAMEENGINE_HPP_

#include "ContextManager.hpp"
#include "MusicManager.hpp"
#include "MusicManager.hpp"
#include "SceneManager.hpp"
#include "Exceptions.h"
#include "ServiceLocator.hpp"

namespace Indie {
    class GameEngine {
        public:
            GameEngine();
            ~GameEngine();

            void startGame();

        private:
            void setupMusicManager();
            void setupSceneManager(Indie::ContextManager &context);

            ContextManager &context;
            Image *loadImage;
    };
}

#endif /* !GAMEENGINE_HPP_ */