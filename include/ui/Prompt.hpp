/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** Prompt
*/

#ifndef PROMPT_HPP_
#define PROMPT_HPP_

#include "Button.hpp"
#include "ContextManager.hpp"
#include "irrlicht.h"
#include <string>
#include <vector>
#include <utility>

namespace Indie
{
    class Prompt
    {
        public:
            Prompt(ContextManager &context);
            ~Prompt() = default;

            void init(std::string const &filepath, int posX, int posY, irr::core::position2d<irr::s32> pos);
            void update(std::pair<int, int> pos);
            void draw();

            std::string getText(void) const;
            void setText(std::string newText);

            static const std::vector<std::pair<irr::EKEY_CODE, std::string>> keyCodes;
            static const std::vector<std::pair<irr::EKEY_CODE, std::string>> keyCodesMaj;
        private:
            ContextManager &context;
            irr::EKEY_CODE key;
            std::string text;
            irr::core::position2d<irr::s32> pos;
            int posX;
            int posY;
            irr::gui::IGUIFont *font;
            Button button;
    };
}

#endif /* !PROMPT_HPP_ */
