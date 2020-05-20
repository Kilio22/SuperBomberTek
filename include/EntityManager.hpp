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
            EntityIterator(EntityManager *entityManager, size_t index, bool isEnd)
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
            EntityManager *entityManager;
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

            const EntityIterator<Types...> &begin()
            {
                return _begin;
            }

            const EntityIterator<Types...> &end()
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
            EntityView<Types...> each()
            {
                return { { this, 0, false }, { this, entities.size(), true } };
            }

            Entity *getByIndex(size_t index)
            {
                return entities[index];
            }

            size_t getCount()
            {
                return this->count;
            }

            // void createGround(irr::core::vector3df const &vector, const std::string &modelPath, const std::string &texturePath, ContextManager &contextManager)
            // {
            //     Entity deglingue;
            //     std::shared_ptr<Components::PositionComponent> xd = std::make_shared<Components::PositionComponent>(vector.X, vector.Y, vector.Z);
            //     std::shared_ptr<Components::RenderComponent> xd2 = std::make_shared<Components::RenderComponent>(modelPath, texturePath, contextManager);

            //     deglingue.addComponent(std::static_pointer_cast<Components::IComponent>(xd));
            //     deglingue.addComponent(std::static_pointer_cast<Components::IComponent>(xd2));

            //     this->entities.push_back(deglingue);
            // }

            // void createWall(irr::core::vector3df &vector);
            // void createPlayer(irr::core::vector3df &vector);
            // void createBomb(irr::core::vector3df &vector);
            // void createIA(irr::core::vector3df &vector);

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
