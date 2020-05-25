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
            TimerComponent(irr::f32 timeToEnd);
            ~TimerComponent() = default;

            irr::f32 getTimePassed(void) const;
            irr::f32 getTimeToEnd(void) const;

            void setTimePassed(irr::f32 timePassed);
            void setTimeToEnd(irr::f32 timeToEnd);

        private:
            irr::f32 timePassed;
            irr::f32 timeToEnd;
    };
} // namespace Indie::Components


#endif /* !TIMERCOMPONENT_HPP_ */
