/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** BombComponent
*/

#ifndef BOMBCOMPONENT_HPP_
#define BOMBCOMPONENT_HPP_

#include <irrlicht.h>

namespace Indie::Components {

class BombComponent {
public:
    BombComponent(int idOwner, unsigned int range);

    unsigned int getRange() const;
    int getIdOwner() const;
    bool hasExploded() const;

    void setRange(unsigned int range);
    void setExploded(bool exploded);

private:
    int idOwner;
    unsigned int range;
    bool exploded;
};

} // namespace Indie::Components

#endif /* !BOMBCOMPONENT_HPP_ */
