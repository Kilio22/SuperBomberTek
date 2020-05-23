/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** SceneManagerException
*/

#include "SceneManagerException.hpp"

Indie::Exceptions::SceneManagerException::SceneManagerException(const std::string &component, const std::string &message)
    : IndieException(component, message)
{
}
