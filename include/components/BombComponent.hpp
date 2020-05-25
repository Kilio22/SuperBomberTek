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
    BombComponent(int idOwner, u_int32_t range);

    u_int32_t getRange() const;
    int getIdOwner() const;

    void setRange(u_int32_t range);

private:
    int idOwner;
    u_int32_t range;
};

} // namespace Indie::Components

#endif /* !BOMBCOMPONENT_HPP_ */
