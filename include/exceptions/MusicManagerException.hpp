/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** MusicManagerException
*/

#ifndef MUSICMANAGEREXCEPTION_HPP_
#define MUSICMANAGEREXCEPTION_HPP_

#include "IndieException.hpp"

namespace Indie::Exceptions
{
    class MusicManagerException : public IndieException
    {
        public:
            MusicManagerException(const std::string &component, const std::string &message);
            ~MusicManagerException() = default;
    };
}

#endif /* !MUSICMANAGEREXCEPTION_HPP_ */