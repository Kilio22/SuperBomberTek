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

struct BombComponent {
    BombComponent();

    irr::f32 ticks;
    bool exploded;
};

} // namespace Indie::Components

#endif /* !BOMBCOMPONENT_HPP_ */
