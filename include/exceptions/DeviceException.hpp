/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** DeviceException | Author: Kylian BALAN - kylian.balan@epitech.eu
*/

#ifndef DEVICEEXCEPTION_HPP_
#define DEVICEEXCEPTION_HPP_

#include "IndieException.hpp"

namespace Indie::Exceptions
{
    class DeviceException : public IndieException
    {
    public:
        DeviceException(const std::string &component, const std::string &message);
        ~DeviceException() = default;
    };
} // namespace Indie::Exceptions

#endif /* !DEVICEEXCEPTION_HPP_ */
