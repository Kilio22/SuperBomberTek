/*
** EPITECH PROJECT, 2019
** editor
** File description:
** Map.hpp
*/

#ifndef CE4340D6_254B_4E4E_9FFF_05CFDE2E3E74
#define CE4340D6_254B_4E4E_9FFF_05CFDE2E3E74

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "enums.hpp"
#include <iostream>

class Map{
    public:
        Map(EDITOR::THEME theme = EDITOR::THEME::LIGHT);
        ~Map();
    
    public:
        void draw(sf::RenderWindow &target);
        void update(sf::RenderWindow &target);
        void setTheme(EDITOR::THEME theme) {_currentTheme = theme;};
        void setBrush(EDITOR::TILETYPE type) {_currentBrush = type;};

        void save(const std::string &filename);

    private:

    private:
        EDITOR::THEME _currentTheme;
        EDITOR::TILETYPE _currentBrush;
        
        EDITOR::TILETYPE _tiles[13][11];

        sf::Texture _texture;
        sf::Sprite _lightThemeSprite[4];
        sf::Sprite _darkThemeSprite[4];
        sf::Sprite _mountainSprite[4];
        sf::Sprite _cursor;
};

#endif /* CE4340D6_254B_4E4E_9FFF_05CFDE2E3E74 */
