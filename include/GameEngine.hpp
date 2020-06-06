/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** GameEngine
*/

#ifndef GAMEENGINE_HPP_
#define GAMEENGINE_HPP_

#include "ContextManager.hpp"

namespace Indie
{
    class GameEngine
    {
    public:
        GameEngine();
        ~GameEngine();

        /**
         * @brief Starts the game
         */
        void startGame(void);

    private:
        void gameLoop(void);
        void setupMusicManager(void);
        void setupSoundManager(void);
        void setupSceneManager(ContextManager &context);

        ContextManager &context;
        Image *loadImage;
    };
}

#endif /* !GAMEENGINE_HPP_ */