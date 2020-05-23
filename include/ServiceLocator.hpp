/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** ServiceLocator
*/

#ifndef SERVICELOCATOR_HPP_
#define SERVICELOCATOR_HPP_

#include "SceneManager.hpp"
#include "MusicManager.hpp"

class ServiceLocator {
    public:
        ServiceLocator() = delete;
        ~ServiceLocator() = delete;

        static void drop();

        static MusicManager musicManager;
        static SceneManager sceneManager;
};

#endif /* !SERVICELOCATOR_HPP_ */