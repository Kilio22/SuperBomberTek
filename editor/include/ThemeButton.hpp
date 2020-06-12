/*
** EPITECH PROJECT, 2019
** editor
** File description:
** ThemeButton.hpp
*/

#ifndef ED8E66F8_F932_40CB_9E41_A876916FAACB
#define ED8E66F8_F932_40CB_9E41_A876916FAACB

#include <SFML/Graphics.hpp>
#include "enums.hpp"

class ThemeButton {
    public:
        ThemeButton(EDITOR::THEME theme = EDITOR::THEME::LIGHT);
        ~ThemeButton() {};

    public:

    private:

    private:
        EDITOR::THEME _theme;

        sf::Texture _idleTexture;
        sf::Texture _selectedTexture;
        sf::Texture _pressedTexture;

        sf::Sprite _idle;
        sf::Sprite _selected;
        sf::Sprite _pressed;

        bool _selectedState;
};

#endif /* ED8E66F8_F932_40CB_9E41_A876916FAACB */
