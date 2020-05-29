/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** TypeIndex
*/

#ifndef TYPEINDEX_HPP_
#define TYPEINDEX_HPP_

#include <typeindex>
#include <typeinfo>

namespace Indie {
    using TypeIndex = std::type_index;

    template <typename T> TypeIndex getTypeIndex()
    {
        return std::type_index(typeid(T));
    }
}

#endif /* !TYPEINDEX_HPP_ */
