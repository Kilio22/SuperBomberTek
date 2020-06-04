/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** WallComponent
*/

#ifndef WALLCOMPONENT_HPP_
#define WALLCOMPONENT_HPP_

namespace Indie::Components
{
    /**
     * @brief Wall component
     */
    class WallComponent
    {
    public:
        WallComponent(bool canBeDestroyed);
        ~WallComponent() = default;

        /**
         * @brief Gets the canBeDestroyed value which is necessary for bomb explosion & wall pass power up
         * @return true The wall can be destroyed
         * @return false The wall is solid
         */
        bool getCanBeDestroyed() const;

    private:
        bool canBeDestroyed;
    };
} // namespace Indie::Components

#endif /* !WALLCOMPONENT_HPP_ */
