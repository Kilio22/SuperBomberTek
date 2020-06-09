/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** EntityManager
*/

#ifndef ENTITYMANAGER_HPP_
#define ENTITYMANAGER_HPP_

#include "Entity.hpp"
#include <algorithm>
#include <iostream>
#include <memory>
#include <unordered_map>
#include <vector>

namespace Indie
{
    class EntityManager;

    template <typename... Types>
    class EntityIterator
    {
        public:
            EntityIterator(const EntityManager *entityManager, size_t index, bool isEnd)
                : entityManager(entityManager)
                , index(index)
                , _isEnd(isEnd)
            {
            }

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
                : _begin(begin)
                , _end(end)
            {
                if (this->_begin.get() == nullptr
                    || this->_begin.get()->isPendingDestroy()
                    || this->_begin.get()->template has<Types...>() == false)
                    ++this->_begin;
            }

            const EntityIterator<Types...> &begin() const
            {
                return this->_begin;
            }

            const EntityIterator<Types...> &end() const
            {
                return this->_end;
            }

        private:
            EntityIterator<Types...> _begin;
            EntityIterator<Types...> _end;
    };

    class EntityManager
    {
        public:
            EntityManager()
                : idCount(0)
            {
            }

            ~EntityManager() = default;

            Entity *createEntity()
            {
                ++this->idCount;
                auto entity = std::make_unique<Entity>(this->idCount);
                auto ptr = entity.get();

                this->entities.push_back(std::move(entity));
                return ptr;
            }

            template <typename T, typename... Args>
            Entity *createUniqueEntity(Args &&... args)
            {
                auto entity = this->createEntity();

                entity->addComponent<T>(std::forward<Args>(args)...);
                this->uniqueEntities.insert({ getTypeIndex<T>(), entity });
                return entity;
            }

            template <typename T>
            Entity *getUniqueEntity()
            {
                return this->uniqueEntities.at(getTypeIndex<T>());
            }

            template <typename... Types>
            EntityView<Types...> each() const
            {
                return { { this, 0, false }, { this, entities.size(), true } };
            }

            Entity *getByIndex(size_t index) const
            {
                if (index >= this->getCount())
                    return nullptr;
                return entities[index].get();
            }

            Entity *getById(int id) const
            {
                for (auto &entity : this->entities) {
                    if (entity->getId() == id)
                        return entity.get();
                }
                return nullptr;
            }

            size_t getCount() const
            {
                return this->entities.size();
            }

            void cleanup()
            {
                size_t nbDeleted = 0;

                for (auto uniqueEntitiesIt = this->uniqueEntities.begin(); uniqueEntitiesIt != this->uniqueEntities.end();) {
                    if (uniqueEntitiesIt->second->isPendingDestroy())
                        this->uniqueEntities.erase(uniqueEntitiesIt);
                    else
                        uniqueEntitiesIt++;
                }
                this->entities.erase(std::remove_if(this->entities.begin(), this->entities.end(), [&](const std::unique_ptr<Entity> &entity) {
                    if (entity->isPendingDestroy()) {
                        ++nbDeleted;
                        return true;
                    }
                    return false;
                }), this->entities.end());
            }

            void reset()
            {
                this->entities.clear();
                this->uniqueEntities.clear();
                idCount = 0;
            }

        private:
            std::vector<std::unique_ptr<Entity>> entities;
            std::unordered_map<TypeIndex, Entity *> uniqueEntities;
            int idCount;
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
        while (this->index < this->entityManager->getCount()
            && (this->get() == nullptr
                || this->get()->isPendingDestroy()
                || this->get()->template has<Types...>() == false))
            ++index;
        if (this->index >= this->entityManager->getCount())
            this->_isEnd = true;
        return *this;
    }
}

#endif /* !ENTITYMANAGER_HPP_ */
