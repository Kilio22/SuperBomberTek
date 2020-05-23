/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** Entity
*/

#ifndef ENTITY_HPP_
#define ENTITY_HPP_

#include <unordered_map>
#include <memory>
#include "ComponentContainer.hpp"
#include "TypeIndex.hpp"

namespace Indie {

class Entity {
    public:
        Entity(int id) : id(id) {}
        ~Entity() = default;

        template<class T>
        bool has()
        {
            return components.find(getTypeIndex<T>()) != components.end();
        }

        template <typename T, typename TNext, typename... TList>
        bool has()
        {
            return this->has<T>() && this->has<TNext, TList...>();
        }

        template <typename T>
        T *getComponent()
        {
            auto container = components.find(getTypeIndex<T>());

            if (container != components.end()) {
                return &reinterpret_cast<ComponentContainer<T> *>(container->second.get())->data;
            }
            return nullptr;
        }

        template <typename T, typename... Args>
        void addComponent(Args &&... args)
        {
            auto ptr = std::make_unique<ComponentContainer<T>>(std::forward<Args>(args)...);

            components.insert({ getTypeIndex<T>(), std::move(ptr) });
        }

    private:
        std::unordered_map<TypeIndex, std::unique_ptr<IComponentContainer>> components;
        int id;
};

}

#endif /* !ENTITY_HPP_ */
