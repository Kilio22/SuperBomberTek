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
#include "ObjectContainer.hpp"
#include "TypeIndex.hpp"

namespace Indie {

class Entity {
    public:
        Entity(int id) : id(id), pendingDestroy(false) {}
        ~Entity() = default;

        template<class T>
        bool has() const
        {
            return components.find(getTypeIndex<T>()) != components.end();
        }

        template <typename T, typename TNext, typename... TList>
        bool has() const
        {
            return this->has<T>() && this->has<TNext, TList...>();
        }

        template <typename T>
        T *getComponent() const
        {
            auto found = components.find(getTypeIndex<T>());

            if (found != components.end()) {
                return &reinterpret_cast<ObjectContainer<T> *>(found->second.get())->data;
            }
            return nullptr;
        }

        template <typename T, typename... Args>
        void addComponent(Args &&... args)
        {
            auto ptr = std::make_unique<ObjectContainer<T>>(std::forward<Args>(args)...);

            components.insert({ getTypeIndex<T>(), std::move(ptr) });
        }

        template <typename T>
        void removeComponent()
        {
            this->components.erase(getTypeIndex<T>());
        }

        void removeAllComponents()
        {
            this->components.clear();
        }

        int getId() const
        {
            return this->id;
        }

        bool isPendingDestroy() const
        {
            return this->pendingDestroy;
        }

        void needDestroy()
        {
            this->pendingDestroy = true;
        }

    private:
        std::unordered_map<TypeIndex, std::unique_ptr<IObjectContainer>> components;
        int id;
        bool pendingDestroy;
};

}

#endif /* !ENTITY_HPP_ */
