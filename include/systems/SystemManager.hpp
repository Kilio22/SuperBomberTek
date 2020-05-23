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
            static SystemManager &getInstance()
            {
                static SystemManager systemManager;

                return systemManager;
            }

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

                systems.insert({ getTypeIndex<T>(), std::move(ptr) });
            }

            SystemManager &operator=(const SystemManager &) = delete;
            SystemManager(SystemManager const &) = delete;

        protected:
        private:
            SystemManager() = default;
            ~SystemManager() = default;

            std::unordered_map<TypeIndex, std::unique_ptr<IComponentContainer>> systems;
    };
} // namespace Indie


#endif /* !SYSTEMMANAGER_HPP_ */
