/*
** EPITECH PROJECT, 2019
** editor
** File description:
** BrushButton.hpp
*/

#ifndef B6900878_B230_49B4_AD4B_06E057DB482C
#define B6900878_B230_49B4_AD4B_06E057DB482C

#include <SFML/Graphics.hpp>
#include "enums.hpp"

class BrushButton : public sf::Drawable, public sf::Transformable {
    public:
        BrushButton(EDITOR::TILETYPE type = EDITOR::TILETYPE::EMPTY);
        ~BrushButton() {};
    
    public:

    private:

    private:
    
};

#endif /* B6900878_B230_49B4_AD4B_06E057DB482C */
