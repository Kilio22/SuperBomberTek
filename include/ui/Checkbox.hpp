/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** Checkbox
*/

#ifndef CHECKBOX_HPP_
#define CHECKBOX_HPP_

#include "ContextManager.hpp"
#include "Button.hpp"
#include <string>
#include <irrlicht.h>

namespace Indie
{
    class Checkbox
    {
        public:
            Checkbox(ContextManager &context);
            ~Checkbox() = default;

            void init(std::string const &filepath, int posX, int posY, irr::core::position2d<irr::s32> pos);
            void update(std::pair<int, int>);
            void draw();
            bool getStatus() const;
            void setStatus(bool status);

        private:
            ContextManager &context;
            bool status;
            Button button;
            irr::core::position2d<irr::s32> pos;
            Image *tick;
    };
}

#endif /* !CHECKBOX_HPP_ */