/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** ComponentContainer
*/

#ifndef COMPONENTCONTAINER_HPP_
#define COMPONENTCONTAINER_HPP_

#include "IComponentContainer.hpp"

namespace Indie {

template <class T>
class ComponentContainer : public IComponentContainer {
public:
    ComponentContainer();
    ComponentContainer(const T &data)
        : data(data) {}

    ~ComponentContainer() = default;

    T data;
};
}

#endif /* !COMPONENTCONTAINER_HPP_ */
