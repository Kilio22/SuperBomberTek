/*
** EPITECH PROJECT, 2019
** editor
** File description:
** ModalSave.hpp
*/

#ifndef CBBD4B62_6610_4B28_BE19_D3B09C261518
#define CBBD4B62_6610_4B28_BE19_D3B09C261518

#include <SFML/Graphics.hpp>

class ModalSave {
    public:
        ModalSave();
        ~ModalSave() {};

    public:
        void draw(sf::RenderWindow &window) const;
        
        bool isCloseHovered(const sf::RenderWindow &window);
        bool isClosePressed(const sf::RenderWindow &window);
        bool isSaveHovered(const sf::RenderWindow &window);
        bool isSavePressed(const sf::RenderWindow &window);


    private:
        sf::Texture _layoutTexture;
        sf::Sprite _layout;

};

#endif /* CBBD4B62_6610_4B28_BE19_D3B09C261518 */
