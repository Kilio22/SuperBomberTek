/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** CameraNotFoundException | Author: Kylian BALAN - kylian.balan@epitech.eu
*/

#ifndef CAMERANOTFOUNDEXCEPTION_HPP_
#define CAMERANOTFOUNDEXCEPTION_HPP_

#include "IndieException.hpp"

namespace Indie::Exceptions
{
    class CameraNotFoundException : public IndieException
    {
        public:
        CameraNotFoundException(const std::string &component, const std::string &message);
        ~CameraNotFoundException() = default;
    };
} // namespace Indie::Exceptions

#endif /* !CAMERANOTFOUNDEXCEPTION_HPP_ */
