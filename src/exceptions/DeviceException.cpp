/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** DeviceException | Author: Kylian BALAN - kylian.balan@epitech.eu
*/

#include "DeviceException.hpp"

Indie::Exceptions::DeviceException::DeviceException(const std::string &component, const std::string &message)
    : IndieException(component, message)
{
}
