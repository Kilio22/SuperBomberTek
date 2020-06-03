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
    /**
     * @brief Timer component
     */
    class TimerComponent
    {
    public:
        TimerComponent(irr::f32 timeToEnd);
        ~TimerComponent() = default;

        /**
         * @brief Gets the passed time
         * @return irr::f32 The passed time
         */
        irr::f32 getTimePassed(void) const;

        /**
         * @brief Gets the time when the timer should flag as being ended
         * @return irr::f32
         */
        irr::f32 getTimeToEnd(void) const;

        /**
         * @brief Sets the time passed
         * @param timePassed The new value
         */
        void setTimePassed(irr::f32 timePassed);

        /**
         * @brief Sets the time to end
         * @param timeToEnd The new value
         */
        void setTimeToEnd(irr::f32 timeToEnd);

    private:
        irr::f32 timePassed;
        irr::f32 timeToEnd;
    };
} // namespace Indie::Components

#endif /* !TIMERCOMPONENT_HPP_ */
