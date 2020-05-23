/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** GameEngine
*/

#ifndef GAMEENGINE_HPP_
#define GAMEENGINE_HPP_

#include "ContextManager.hpp"
#include "ServiceLocator.hpp"

namespace Indie {
    class GameEngine {
        public:
            GameEngine()
                : context(Indie::ServiceLocator::getInstance().get<ContextManager>())
            {
            }

            ~GameEngine() = default;

            void startGame();

        private:
            ContextManager &context;
    };
}

#endif /* !GAMEENGINE_HPP_ */