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
    class WallComponent
    {
        public:
            WallComponent();
            ~WallComponent() = default;

            bool getCanBeDestroyed() const;
            void setCanBeDestroyed(bool);

        protected:
        private:
            bool canBeDestroyed;
    };
} // namespace Indie::Components


#endif /* !WALLCOMPONENT_HPP_ */
