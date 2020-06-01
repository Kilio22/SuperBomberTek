/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** ServiceLocator
*/

#ifndef SERVICELOCATOR_HPP_
#define SERVICELOCATOR_HPP_

#include "SceneManager.hpp"
#include "MusicManager.hpp"
#include "ImageLoader.hpp"

namespace Indie
{
    class ServiceLocator
    {
        private:
            ServiceLocator() = default;

        public:
            ServiceLocator(const ServiceLocator &) = delete;
            ~ServiceLocator() = default;
            ServiceLocator &operator=(const ServiceLocator &) = delete;

            static ServiceLocator &getInstance()
            {
                static ServiceLocator serviceLocator;

                return serviceLocator;
            }

            template <typename T>
            T &get()
            {
                static T service;

                return service;
            }
    };
}

#endif /* !SERVICELOCATOR_HPP_ */