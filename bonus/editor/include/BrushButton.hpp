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
        BrushButton();
        ~BrushButton() {};
    
    public:
        virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;
        void update(const sf::RenderWindow &window);
        bool isButtonHover(int mx, int my) const;
        bool isButtonClicked(int mx, int my) const;
        void setSelected(bool selected) {_selectedState = selected;};
        bool getSelected() const {return _selectedState;};

    private:

    private:
        sf::Texture _idleTexture;
        sf::Texture _pressedTexture;
        sf::Texture _selectedTexture;

        sf::Sprite _idle;
        sf::Sprite _pressed;
        sf::Sprite _selected;

        bool _selectedState;
        bool _pressedState;
};

#endif /* B6900878_B230_49B4_AD4B_06E057DB482C */
