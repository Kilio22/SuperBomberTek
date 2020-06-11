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

class Map : public sf::Drawable{
    public:
        enum TileType {EMPTY, UNDESTRUCTIBLE, DESTRUCTIBLE};

    public:
        Map();
        ~Map();
    
    public:
        virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;

    private:

    private:
        TileType _tiles[13][15];
};

#endif /* CE4340D6_254B_4E4E_9FFF_05CFDE2E3E74 */
