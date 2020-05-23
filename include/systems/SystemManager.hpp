/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** SystemManager
*/

#ifndef SYSTEMMANAGER_HPP_
#define SYSTEMMANAGER_HPP_

#include <unordered_map>
#include <memory>
#include "ISystem.hpp"
#include "TypeIndex.hpp"
#include "ComponentContainer.hpp"

namespace Indie
{
    class SystemManager
    {
        public:
            SystemManager() = default;
            ~SystemManager() = default;

            template <typename T>
            T *getSystem()
            {
                auto container = systems.find(getTypeIndex<T>());

                if (container != systems.end()) {
                    return &reinterpret_cast<ComponentContainer<T> *>(container->second.get())->data;
                }
                return nullptr;
            }

            template <typename T, typename... Args>
            void addSystem(Args &&... args)
            {
                auto ptr = std::make_unique<ComponentContainer<T>>(std::forward<Args>(args)...);

                components.insert({ getTypeIndex<T>(), std::move(ptr) });
            }

        protected:
        private:
            std::unordered_map<TypeIndex, std::unique_ptr<Indie::Systems::ISystem>> systems;
    };
} // namespace Indie


#endif /* !SYSTEMMANAGER_HPP_ */
