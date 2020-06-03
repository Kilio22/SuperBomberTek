/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** MoveComponent
*/

#ifndef MOVECOMPONENT_HPP_
#define MOVECOMPONENT_HPP_

#include "ContextManager.hpp"
#include <string>

namespace Indie::Components
{
    /**
     * @brief Move component
     */
    class MoveComponent
    {
    public:
        MoveComponent();
        ~MoveComponent() = default;

        /**
         * @brief Sets up state
         */
        void setUp(bool);

        /**
         * @brief Sets down state
         */
        void setDown(bool);

        /**
         * @brief Sets left state
         */
        void setLeft(bool);

        /**
         * @brief Sets right state
         */
        void setRight(bool);

        /**
         * @brief Sets drip state
         */
        void setDrop(bool);

        /**
         * @brief Gets up state
         * @return true Should move up
         * @return false Shouldn't move up
         */
        bool getUp(void) const;

        /**
         * @brief Get down state
         * @return true Should move down
         * @return false Shouldn't move down
         */
        bool getDown(void) const;

        /**
         * @brief Gets left state
         * @return true Should move left
         * @return false Shouldn't move left
         */
        bool getLeft(void) const;

        /**
         * @brief Gets right state
         * @return true Should move right
         * @return false Shouldn't move right
         */
        bool getRight(void) const;

        /**
         * @brief Gets drop state
         * @return true Should drop bomb
         * @return false Shouldn't drop bomb
         */
        bool getDrop(void) const;

    private:
        bool up;
        bool down;
        bool left;
        bool right;
        bool drop;
    };
}

#endif /* !MOVECOMPONENT_HPP_ */
