/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** Bar
*/

#ifndef BAR_HPP_
#define BAR_HPP_

#include "ContextManager.hpp"
#include "irrlicht.h"
#include <string>

namespace Indie {
    class Bar {
        public:
            Bar(ContextManager &context);
            ~Bar() = default;

            void init(const std::string &filepath, int min, int max, int current);
            void update();
            void setSize(int min, int max);
            void setValue(int value);
            void setLevel(int level);
            void draw(irr::core::position2d<irr::s32> pos) const;

        protected:
        //private:
        //    float getPercentage(Indie::MasterInfo &info);
        private:
            ContextManager &context;
            int min;
            int max;
            int value;
            int percentage;
            int level;
            irr::gui::IGUIFont *font;
            Image *empty;
            Image *full;
            Image *layout;
    };
}

#endif /* !BAR_HPP_ */