/*
** EPITECH PROJECT, 2019
** editor
** File description:
** Editor.hpp
*/

#ifndef C603948F_E38D_48C5_B016_BC3B0C1DF8F4
#define C603948F_E38D_48C5_B016_BC3B0C1DF8F4

#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <memory>

class Editor {
    public:
        Editor();
        ~Editor();
    
    public:
        void loop();

    private:
        void clear();
        void update();
        void render();

    private:
        sf::RenderWindow _window;
};

#endif /* C603948F_E38D_48C5_B016_BC3B0C1DF8F4 */
