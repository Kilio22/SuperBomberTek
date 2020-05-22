/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** main
*/

#include <exception>
#include "GameEngine.hpp"
#include "Exceptions.h"

int main(void)
{
    GameEngine engine;

    try
    {
        engine.startGame();
    }
    catch(const Indie::Exceptions::IndieException &e) {
        std::cerr << "In component \"" << e.getComponent() << "\": " << e.what() << '\n';
        return 84;
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        return 84;
    }
    return 0;
}