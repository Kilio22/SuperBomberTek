/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** Entity
*/

#ifndef IENTITY_HPP_
#define IENTITY_HPP_

#include <vector>
#include <memory>
#include "IComponent.hpp"

namespace Indie
{
    class IEntity
    {
        public:
            virtual ~IEntity() = default;

            // template<class T>
            // virtual std::unique_ptr<T> getComponent(int componentId) = 0;

            virtual void addComponent(std::unique_ptr<Components::IComponent> component) = 0;
            virtual void removeComponent(std::unique_ptr<Components::IComponent> component) = 0;
    };
}

#endif /* !IENTITY_HPP_ */
