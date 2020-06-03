/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** PowerDownComponent | Author: Kylian BALAN - kylian.balan@epitech.eu
*/

#ifndef POWERDOWNCOMPONENT_HPP_
#define POWERDOWNCOMPONENT_HPP_

namespace Indie::Components
{
    enum class POWERDOWN_TYPE { BOMB_DOWN, FIRE_DOWN, SPEED_DOWN, NONE };

    class PowerDownComponent
    {

        public:
        PowerDownComponent(POWERDOWN_TYPE type);
        ~PowerDownComponent() = default;

        POWERDOWN_TYPE getType(void) const;
        void setType(POWERDOWN_TYPE type);

        private:
        POWERDOWN_TYPE type;
    };
} // namespace Indie::Components

#endif /* !POWERDOWNCOMPONENT_HPP_ */
