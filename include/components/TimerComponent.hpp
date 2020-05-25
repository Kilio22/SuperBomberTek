/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** TimerComponent
*/

#ifndef TIMERCOMPONENT_HPP_
#define TIMERCOMPONENT_HPP_

#include <irrlicht.h>

namespace Indie::Components
{
    class TimerComponent
    {
        public:
            TimerComponent(irr::f32 seconds);
            ~TimerComponent() = default;

            irr::f32 getTicks(void) const;
            irr::f32 getSeconds(void) const;

            void setTicks(irr::f32 value);
            void setSeconds(irr::f32 value);

        protected:
        private:
            irr::f32 ticks;
            irr::f32 seconds;
    };
} // namespace Indie::Components


#endif /* !TIMERCOMPONENT_HPP_ */
