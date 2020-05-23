/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** MusicManagerException
*/

#include "MusicManagerException.hpp"

Indie::Exceptions::MusicManagerException::MusicManagerException(const std::string &component, const std::string &message)
    : IndieException(component, message)
{
}
