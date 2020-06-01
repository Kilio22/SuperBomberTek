/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** KillComponent
*/

#ifndef KILLCOMPONENT_HPP_
#define KILLCOMPONENT_HPP_

namespace Indie::Components
{
    class KillComponent
    {
    public:
        KillComponent(int ownerId = -1);
        ~KillComponent() = default;

        int getOwnerId() const;

    private:
        int ownerId;
    };
} // namespace Indie::Components

#endif /* !KILLCOMPONENT_HPP_ */
