/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** EntityManager
*/

#ifndef ENTITYMANAGER_HPP_
#define ENTITYMANAGER_HPP_

#include <vector>
#include <memory>
#include <iostream>
#include "Entity.hpp"

namespace Indie
{
    class EntityManager;

    template <typename... Types>
    class EntityIterator
    {
        public:
            EntityIterator(const EntityManager *entityManager, size_t index, bool isEnd)
                : entityManager(entityManager), index(index), _isEnd(isEnd) {}

            bool isEnd() const;

            Entity *get() const;

            Entity *operator*() const
            {
                return get();
            }

            bool operator==(const EntityIterator<Types...> &rhs) const
            {
                if (this->entityManager != rhs.entityManager)
                    return false;
                if (this->isEnd())
                    return rhs.isEnd();
                return this->index == rhs.index;
            }

            bool operator!=(const EntityIterator<Types...> &rhs) const
            {
                if (this->entityManager != rhs.entityManager)
                    return true;
                if (this->isEnd())
                    return !rhs.isEnd();
                return this->index != rhs.index;
            }

            EntityIterator<Types...> &operator++();

        private:
            const EntityManager *entityManager;
            size_t index;
            bool _isEnd;
    };

    template <typename... Types>
    class EntityView
    {
        public:
            EntityView(EntityIterator<Types...> begin, EntityIterator<Types...> end)
                : _begin(begin), _end(end)
            {
                if (this->_begin.get()->template has<Types...>() == false)
                    ++this->_begin;
            }

            const EntityIterator<Types...> &begin() const
            {
                return _begin;
            }

            const EntityIterator<Types...> &end() const
            {
                return _end;
            }

        private:
            EntityIterator<Types...> _begin;
            EntityIterator<Types...> _end;
    };

    class EntityManager
    {
        public:
            EntityManager() : count(0) {}
            ~EntityManager() = default;

            Entity *createEntity()
            {
                ++this->count;
                Entity *entity = new Entity(this->count);

                this->entities.push_back(entity);
                return entity;
            }

            template <typename... Types>
            EntityView<Types...> each() const
            {
                return { { this, 0, false }, { this, entities.size(), true } };
            }

            Entity *getByIndex(size_t index) const
            {
                return entities[index];
            }

            size_t getCount() const
            {
                return this->count;
            }

        private:
            std::vector<Entity *> entities;
            size_t count;
    };

    template <typename... Types>
    bool EntityIterator<Types...>::isEnd() const
    {
        return this->_isEnd || this->index >= this->entityManager->getCount();
    }

    template <typename... Types>
    Entity *EntityIterator<Types...>::get() const
    {
        if (this->isEnd() == true)
            return nullptr;
        return this->entityManager->getByIndex(this->index);
    }

    template <typename... Types>
    EntityIterator<Types...> &EntityIterator<Types...>::operator++()
    {
        ++index;
        while (this->index < this->entityManager->getCount() && this->get()->template has<Types...>() == false) {
            ++index;
        }
        return *this;
    }
}

#endif /* !ENTITYMANAGER_HPP_ */
