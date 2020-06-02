/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** CameraNotFoundException | Author: Kylian BALAN - kylian.balan@epitech.eu
*/

#include "CameraNotFoundException.hpp"

Indie::Exceptions::CameraNotFoundException::CameraNotFoundException(const std::string &component, const std::string &message)
    : IndieException(component, message)
{
}
