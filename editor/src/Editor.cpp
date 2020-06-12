/*
** EPITECH PROJECT, 2019
** editor
** File description:
** Editor.cpp
*/

#include "Editor.hpp"

Editor::Editor() :
    _window(sf::VideoMode(700, 436), "Indie Map Editor")
{
    _music.openFromFile("assets/main_menu_loop.wav");
    _music.setLoop(true);
    _music.play();

    _window.setFramerateLimit(60);
    _map.setTheme(EDITOR::THEME::MOUNTAIN);
    _themeVizualizer.setScale(5, 5);
    _themeVizualizer.setPosition(sf::Vector2f(00, 00));
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
    _themeVizualizer.update();
    _map.update(_window);
}

void Editor::render() {
    _window.draw(_hud);
    _map.draw(_window);
    _window.display();
}