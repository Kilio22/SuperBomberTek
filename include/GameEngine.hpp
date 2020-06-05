/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** GameEngine
*/

#ifndef GAMEENGINE_HPP_
#define GAMEENGINE_HPP_

#include "ContextManager.hpp"
#include "Exceptions.h"
#include "MusicManager.hpp"
#include "SceneManager.hpp"
#include "ServiceLocator.hpp"

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
        void startGame();

    private:
        void readOptions();
        std::string findValueByName(std::vector<std::vector<std::string>> parsedData, const std::string &value) const;
        void setupMusicManager();
        void setupSoundManager();
        void setupSceneManager(Indie::ContextManager &context);

        ContextManager &context;
        Image *loadImage;
    };
}

#endif /* !GAMEENGINE_HPP_ */