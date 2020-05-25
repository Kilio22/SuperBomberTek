/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** SceneNotFoundException
*/

#include "SceneNotFoundException.hpp"

Indie::Exceptions::SceneNotFoundException::SceneNotFoundException(const std::string &component, const std::string &message)
    : IndieException(component, message)
{
}
