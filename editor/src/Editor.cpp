/*
** EPITECH PROJECT, 2019
** editor
** File description:
** Editor.cpp
*/

#include "Editor.hpp"

Editor::Editor() :
    _window(sf::VideoMode(800, 600), "Indie Map Editor")
{
    
}

Editor::~Editor() {

}

void Editor::loop() {
    while (_window.isOpen()) {
        sf::Event ev;
        while (_window.pollEvent(ev)) {
            if (ev.type == sf::Event::Closed)
                _window.close();
        }
        clear();
        update();
        render();
    }
}

void Editor::clear() {
    _window.clear(sf::Color::Black);
}

void Editor::update() {
    _window.draw(_map);
}

void Editor::render() {
    _window.display();
}