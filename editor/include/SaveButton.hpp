/*
** EPITECH PROJECT, 2019
** editor
** File description:
** SaveButton.hpp
*/

#ifndef E9E44474_630E_4EBC_8AA1_FE1D4D3DD688
#define E9E44474_630E_4EBC_8AA1_FE1D4D3DD688

#include <SFML/Graphics.hpp>

class SaveButton : public sf::Drawable, public sf::Transformable {
    public:
        SaveButton();
        ~SaveButton() {};
    
    public:
        virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;
        void update(const sf::RenderWindow &window);
        bool isButtonHover(int mx, int my) const;
        bool isButtonClicked(int mx, int my) const;

    private:
        sf::Texture _idleTexture;
        sf::Texture _hoveredTexture;
        sf::Texture _pressedTexture;

        sf::Sprite _idle;
        sf::Sprite _hovered;
        sf::Sprite _pressed;

        bool _hoveredState;
        bool _clickedState;
};

#endif /* E9E44474_630E_4EBC_8AA1_FE1D4D3DD688 */
