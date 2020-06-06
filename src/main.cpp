/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** main
*/

#include "Exceptions.h"
#include "GameEngine.hpp"
#include <exception>
#include <iostream>
#include <ctime>

int main(void)
{
    std::srand((unsigned int)time(NULL));
    Indie::GameEngine engine;

    try {
        engine.startGame();
    } catch (const Indie::Exceptions::IndieException &e) {
        std::cerr << "In component \"" << e.getComponent() << "\": " << e.what() << std::endl;
        return 84;
    } catch (const std::exception &e) {
        std::cerr << "Unexpected exception: '" << e.what() << "'" << std::endl;
        return 84;
    }
    return 0;
}
