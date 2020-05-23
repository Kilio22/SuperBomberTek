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

//TODO : Add include for EventHandler

namespace Indie {
    class GameEngine {
        public:
            GameEngine();
            ~GameEngine() = default;

            void startGame();

        private:
            ContextManager &context;
    };
}

#endif /* !GAMEENGINE_HPP_ */