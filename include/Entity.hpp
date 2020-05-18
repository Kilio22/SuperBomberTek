/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** Entity
*/

#ifndef ENTITY_HPP_
#define ENTITY_HPP_

#include <vector>
#include <memory>
#include "IComponent.hpp"
// #include "IEntity.hpp"

namespace Indie
{
    class Entity/*  : public IEntity */
    {
        public:
            Entity() = default;
            ~Entity() = default;

            template<class T>
            std::shared_ptr<T> getComponent(int componentId)
            {
                if (this->components[componentId] == nullptr) {
                    return nullptr;
                }
                return std::static_pointer_cast<T>(this->components[componentId]);
            }

            bool hasComponent(int componentId)
            {
                if (this->components[componentId] == nullptr)
                    return false;
                return true;
            }

            void addComponent(std::shared_ptr<Components::IComponent> component)
            {
                this->components.push_back(component);
            }

            void removeComponent(std::shared_ptr<Components::IComponent>)
            {
            }

        private:
            std::vector<std::shared_ptr<Components::IComponent>> components;
            int id;
    };
}

#endif /* !ENTITY_HPP_ */
