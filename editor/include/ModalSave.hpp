/*
** EPITECH PROJECT, 2019
** editor
** File description:
** ModalSave.hpp
*/

#ifndef CBBD4B62_6610_4B28_BE19_D3B09C261518
#define CBBD4B62_6610_4B28_BE19_D3B09C261518

#include <SFML/Graphics.hpp>
#include <iostream>

class ModalSave {
    public:
        ModalSave();
        ~ModalSave() {};

    public:
        void draw(sf::RenderWindow &window) const;
        void update(sf::RenderWindow &window);

        bool isCloseHovered(const sf::RenderWindow &window) const;
        bool isClosePressed(const sf::RenderWindow &window) const;
        bool isSaveHovered(const sf::RenderWindow &window) const;
        bool isSavePressed(const sf::RenderWindow &window) const;


    private:
        sf::Texture _layoutTexture;

        sf::Texture _crossIdleTexture;
        sf::Texture _crossSelectedTexture;
        sf::Texture _crossPressedTexture;

        sf::Texture _saveIdleTexture;
        sf::Texture _saveSelectedTexture;
        sf::Texture _savePressedTexture;

        sf::Sprite _layout;

        sf::Sprite _crossIdle;
        sf::Sprite _crossSelected;
        sf::Sprite _crossPressed;

        sf::Sprite _saveIdle;
        sf::Sprite _saveSelected;
        sf::Sprite _savePressed;
};

#endif /* CBBD4B62_6610_4B28_BE19_D3B09C261518 */
