/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** IndieException
*/

#include "IndieException.hpp"

Indie::Exceptions::IndieException::IndieException(const std::string &component, const std::string &message)
    : _component(component), _message(message)
{
}

const char *Indie::Exceptions::IndieException::what() const noexcept
{
    return this->_message.c_str();
}

std::string const &Indie::Exceptions::IndieException::getComponent(void) const noexcept
{
    return this->_component;
}
