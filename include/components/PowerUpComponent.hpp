/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** PowerUpComponent
*/

#ifndef POWERUPCOMPONENT_HPP_
#define POWERUPCOMPONENT_HPP_

namespace Indie::Components
{
    enum class POWERUP_TYPE {
        BOMB_UP,
        FIRE_UP,
        SPEED_UP,
        WALL_PASS,
        NONE
    };

    class PowerUpComponent
    {
        public:
            PowerUpComponent(POWERUP_TYPE type);
            ~PowerUpComponent() = default;

            POWERUP_TYPE getType(void) const;
            void getType(POWERUP_TYPE type);

        private:
            POWERUP_TYPE type;
    };
} // namespace Indie::Components


#endif /* !POWERUPCOMPONENT_HPP_ */
