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
    _music.setVolume(20);
    _music.play();

    _window.setFramerateLimit(60);
    _map.setTheme(EDITOR::THEME::MOUNTAIN);
    _themeVizualizer.setScale(5, 5);
    _themeVizualizer.setPosition(sf::Vector2f(00, 00));
    _modalState = false;
}

Editor::~Editor() {
    _music.stop();
}

void Editor::loop() {
    sf::View view;

    view.setCenter({350, 218});
    view.setSize({700, 436});
    while (_window.isOpen()) {
        _window.setView(view);
        sf::Event ev;
        while (_window.pollEvent(ev)) {
            if (ev.type == sf::Event::Closed)
                _window.close();
            if (ev.type == sf::Event::TextEntered && _modalState) {
                if (ev.text.unicode < 128) {
                    char c = static_cast<char>(ev.text.unicode);
                    if ((int)c == 8) {
                        if (!_fileState.empty())
                            _fileState.pop_back();
                    } else if (_fileState.length() < 16) {
                        _fileState.push_back(c);
                    }
                    _modalSave.setFileState(_fileState);
                }
            }
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
    if (!_modalState) {
        _map.update(_window);
        _hud.update(_window);
        _map.setTheme(_hud.getThemeState());
        _map.setBrush(_hud.getBrushState());
        if (_hud.savePressed(_window))
            _modalState = true;
    } else {
        if (_modalSave.isClosePressed(_window))
            _modalState = false;
        else if (_modalSave.isSavePressed(_window) && !_fileState.empty()) {
            _window.close();
            _map.save(_fileState);
        }
    }
}

void Editor::render() {
    _hud.draw(_window);
    _map.draw(_window);
    if (_modalState) {
        _modalSave.draw(_window);
    }
    _window.display();
}