/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** InvalidIndexException
*/

#include "InvalidIndexException.hpp"

Indie::Exceptions::InvalidIndexException::InvalidIndexException(const std::string &component, const std::string &message)
    : IndieException(component, message)
{
}
