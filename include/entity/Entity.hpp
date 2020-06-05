/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** Entity
*/

#ifndef ENTITY_HPP_
#define ENTITY_HPP_

#include "ObjectContainer.hpp"
#include "TypeIndex.hpp"
#include <memory>
#include <unordered_map>

namespace Indie
{

    /**
     * @brief The Entity class
     */
    class Entity
    {
    public:
        Entity(int id)
            : id(id)
            , pendingDestroy(false)
        {
        }
        ~Entity() = default;

        /**
         * @brief Checks if the entity has the T component
         *
         * @tparam T The component
         * @return true The entity has the given component
         * @return false The entity hasn't the given component
         */
        template <class T>
        bool has() const
        {
            return components.count(getTypeIndex<T>()) > 0;
        }

        /**
         * @brief Checks if the entity has all given components
         *
         * @tparam T The component to check
         * @tparam TNext The next component to check
         * @tparam TList The rest of the list
         * @return true The component has all given components
         * @return false The component hasn't all given components
         */
        template <typename T, typename TNext, typename... TList>
        bool has() const
        {
            return this->has<T>() && this->has<TNext, TList...>();
        }

        /**
         * @brief Gets wanted component
         *
         * @tparam T The component to get
         * @return T* The component found
         */
        template <typename T>
        T *getComponent() const
        {
            auto &ptr = components.at(getTypeIndex<T>());

            return &reinterpret_cast<ObjectContainer<T> *>(ptr.get())->data;
        }

        /**
         * @brief Adds a component to the entity
         *
         * @tparam T the component to add
         * @tparam Args Component's ctor args
         * @param args Component's ctor args
         */
        template <typename T, typename... Args>
        void addComponent(Args &&... args)
        {
            auto ptr = std::make_unique<ObjectContainer<T>>(std::forward<Args>(args)...);

            components.insert({ getTypeIndex<T>(), std::move(ptr) });
        }

        /**
         * @brief Removes given component
         *
         * @tparam T The component to remove
         */
        template <typename T>
        void removeComponent()
        {
            this->components.erase(getTypeIndex<T>());
        }

        /**
         * @brief Deletes all components of the entity
         */
        void removeAllComponents()
        {
            this->components.clear();
        }

        /**
         * @brief Gets the entity's id
         *
         * @return int
         */
        int getId() const
        {
            return this->id;
        }

        /**
         * @brief Checks if the entity must be destroyed
         *
         * @return true The entity must be destroyed
         * @return false The entity shouldn't be destroyed
         */
        bool isPendingDestroy() const
        {
            return this->pendingDestroy;
        }

        /**
         * @brief By calling this, the entity is set as it will be destroyed soon
         */
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
