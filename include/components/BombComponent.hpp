/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** BombComponent
*/

#ifndef BOMBCOMPONENT_HPP_
#define BOMBCOMPONENT_HPP_

namespace Indie::Components
{
    /**
     * @brief Bomb component
     */
    class BombComponent
    {
    public:
        BombComponent(int idOwner, unsigned int range);

        /**
         * @brief Gets the range of the bomb
         * @return The bomb range
         */
        unsigned int getRange() const;

        /**
         * @brief Gets the Id of the player who droped the bomb
         * @return The player's Id
         */
        int getIdOwner() const;

        /**
         * @brief Checks if the bomb has exploded
         * @return true Bomb has exploded
         * @return false Bomb hasn't exploded yet
         */
        bool hasExploded() const;

        /**
         * @brief Sets the Range of the bomb
         * @param range The range
         */
        void setRange(unsigned int range);

        /**
         * @brief Sets bomb status
         * @param exploded True if the bomb has exploded, false otherwise
         */
        void setExploded(bool exploded);

    private:
        int idOwner;
        unsigned int range;
        bool exploded;
    };

} // namespace Indie::Components

#endif /* !BOMBCOMPONENT_HPP_ */
