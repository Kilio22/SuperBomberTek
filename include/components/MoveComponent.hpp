/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** MoveComponent
*/

#ifndef MOVECOMPONENT_HPP_
#define MOVECOMPONENT_HPP_

#include <vector>
#include <string>
#include "IComponent.hpp"
#include "ContextManager.hpp"

namespace Indie::Components
{
    class MoveComponent : public IComponent
    {
        public:
            MoveComponent();
            ~MoveComponent() = default;

            void setUp(bool);
            void setDown(bool);
            void setLeft(bool);
            void setRight(bool);
            void setDrop(bool);

            bool getUp();
            bool getDown();
            bool getLeft();
            bool getRight();
            bool getDrop();

        protected:
        private:
            bool up;
            bool down;
            bool left;
            bool right;
            bool drop;
    };
}


#endif /* !MOVECOMPONENT_HPP_ */
