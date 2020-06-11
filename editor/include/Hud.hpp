/*
** EPITECH PROJECT, 2019
** editor
** File description:
** Hud.hpp
*/

#ifndef CB9DE120_D7FF_4148_B222_EB099879ABE3
#define CB9DE120_D7FF_4148_B222_EB099879ABE3

#include <SFML/Graphics.hpp>

class Hud : public sf::Drawable {
    public:
        Hud();
        ~Hud();

    public:
        virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;

    private:
};

#endif /* CB9DE120_D7FF_4148_B222_EB099879ABE3 */
