/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** Button
*/

#ifndef BUTTON_HPP_
#define BUTTON_HPP_

#include "ContextManager.hpp"
#include "EventHandler.hpp"
#include "Exceptions.h"
#include <string>
#include <vector>
#include <irrlicht.h>

#define SELECTBUTTON (irr::EKEY_CODE::KEY_RETURN)

namespace Indie {
    class Button {
        public:
            Button(ContextManager &context);
            ~Button();

            enum class Status : int {
                    Idle,
                    Selected,
                    Pressed
                };

            void init(ContextManager &context, const std::string &filepath, int posX, int posY, irr::core::position2d<irr::s32> pos);
            void update(std::pair<int, int>);
            void draw();
            Status getStatus() const;

        protected:
        private:
            ContextManager &context;
            int posX;
            int posY;
            Status status;
            bool keyPressed;
            irr::core::position2d<irr::s32> pos;
            irr::core::rect<irr::s32> size;
            Image *idle;
            Image *selected;
            Image *pressed;
    };
}

#endif /* !BUTTON_HPP_ */
