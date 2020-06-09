/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** main
*/

#include "Exceptions.h"
#include "GameEngine.hpp"
#include <ctime>
#include <exception>
#include <iostream>

int main(void)
{
    std::srand((unsigned int)time(NULL));

    try {
        Indie::GameEngine engine;

        engine.startGame();
    } catch (const Indie::Exceptions::IndieException &e) {
        std::cerr << e.getComponent() << ": " << e.what() << std::endl;
        return 84;
    } catch (const std::exception &e) {
        std::cerr << "Unexpected exception: '" << e.what() << "'" << std::endl;
        return 84;
    }
    return 0;
}
