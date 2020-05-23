/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** MoveComponent
*/

#ifndef MOVECOMPONENT_HPP_
#define MOVECOMPONENT_HPP_

#include <string>
#include "ContextManager.hpp"

namespace Indie::Components
{
    class MoveComponent
    {
        public:
            MoveComponent();
            ~MoveComponent() = default;

            void setUp(bool);
            void setDown(bool);
            void setLeft(bool);
            void setRight(bool);
            void setDrop(bool);

            bool getUp(void) const;
            bool getDown(void) const;
            bool getLeft(void) const;
            bool getRight(void) const;
            bool getDrop(void) const;

        private:
            bool up;
            bool down;
            bool left;
            bool right;
            bool drop;
    };
}


#endif /* !MOVECOMPONENT_HPP_ */
