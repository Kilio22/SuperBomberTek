/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** FileNotFoundException
*/

#include "FileNotFoundException.hpp"

Indie::Exceptions::FileNotFoundException::FileNotFoundException(const std::string &component, const std::string &message)
    : IndieException(component, message)
{
}
