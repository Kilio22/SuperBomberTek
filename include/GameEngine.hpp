/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** GameEngine
*/

#ifndef GAMEENGINE_HPP_
#define GAMEENGINE_HPP_

#include <irrlicht.h>
#include <iostream>
#include "EntityManager.hpp"
#include "RenderSystem.hpp"
#include "ContextManager.hpp"
#include "MusicManager.hpp"
#include "SceneManager.hpp"
#include "MusicManager.hpp"
#include "SceneManager.hpp"
//TODO : Add include for EventHandler

class GameEngine {
    public:
        GameEngine() : context(DIM(1280, 720)) {}
        ~GameEngine() {}

        void startGame();
    private:
        ContextManager context;
        //TODO : Add EventHandler here
};

#endif /* !GAMEENGINE_HPP_ */