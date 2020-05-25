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

    void setRange(unsigned int range);

private:
    int idOwner;
    unsigned int range;
};

} // namespace Indie::Components

#endif /* !BOMBCOMPONENT_HPP_ */
