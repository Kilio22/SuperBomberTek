/*
** EPITECH PROJECT, 2019
** editor
** File description:
** Hud.hpp
*/

#ifndef CB9DE120_D7FF_4148_B222_EB099879ABE3
#define CB9DE120_D7FF_4148_B222_EB099879ABE3

#include <SFML/Graphics.hpp>
#include "enums.hpp"
#include "ThemeButton.hpp"
#include "BrushButton.hpp"
#include "SaveButton.hpp"

class Hud {
    public:
        Hud();
        ~Hud();

    public:
        void draw(sf::RenderWindow &window);
        void update(const sf::RenderWindow &window);

        EDITOR::TILETYPE getBrushState() const {return _brushState;};
        EDITOR::THEME getThemeState() const {return _themeState;};

    private:
        EDITOR::TILETYPE _brushState;
        EDITOR::THEME _themeState;

        ThemeButton _lightSelector;
        ThemeButton _darkSelector;
        ThemeButton _mountainSelector;

        BrushButton _emptySelector;
        BrushButton _destructibleSelector;
        BrushButton _undestructibleSelector;

        SaveButton _saveButton;

        sf::Texture _placeholerTexture;
        sf::Sprite _placeholder;
};

#endif /* CB9DE120_D7FF_4148_B222_EB099879ABE3 */
