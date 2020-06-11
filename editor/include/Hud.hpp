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
        enum Brush {EMPTY = -1, RUBBER, UNDESTRUCTIBLE, DESTRUCTIBLE};

    public:
        Hud();
        ~Hud();

    public:
        virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;
        void update(const sf::RenderWindow &window);
        
        Brush getBrushState() const {return _brushState;};

    private:
        Brush _brushState;
};

#endif /* CB9DE120_D7FF_4148_B222_EB099879ABE3 */
