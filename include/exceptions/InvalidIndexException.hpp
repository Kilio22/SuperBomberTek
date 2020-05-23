/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** InvalidIndexException
*/

#ifndef INVALIDINDEXEXCEPTION_HPP_
#define INVALIDINDEXEXCEPTION_HPP_

#include "IndieException.hpp"

namespace Indie::Exceptions
{
    class InvalidIndexException : public IndieException
    {
        public:
            InvalidIndexException(const std::string &component, const std::string &message);
            ~InvalidIndexException() = default;
    };
}

#endif /* !INVALIDINDEXEXCEPTION_HPP_ */
