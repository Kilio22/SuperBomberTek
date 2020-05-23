/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** ObjectContainer
*/

#ifndef COMPONENTCONTAINER_HPP_
#define COMPONENTCONTAINER_HPP_

#include "IObjectContainer.hpp"

namespace Indie {

template <class T>
class ObjectContainer : public IObjectContainer {
    public:
        template <typename... Args>
        ObjectContainer(Args &&... args)
            : data(std::forward<Args>(args)...) {}

        ~ObjectContainer() = default;

        T data;
};

}

#endif /* !COMPONENTCONTAINER_HPP_ */
