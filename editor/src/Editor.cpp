/*
** EPITECH PROJECT, 2019
** editor
** File description:
** Editor.cpp
*/

#include "Editor.hpp"

Editor::Editor() :
    _window(sf::VideoMode(636, 500), "Indie Map Editor")
{
    _window.setFramerateLimit(60);

    _themeVizualizer.setPosition(100, 100);
    _themeVizualizer.setScale(4, 4);
    _themeVizualizer.setTheme(ThemeVizualizer::THEME::DARK);
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
}

void Editor::render() {
    _window.draw(_map);
    _window.draw(_hud);
    _window.draw(_themeVizualizer);
    _window.display();
}