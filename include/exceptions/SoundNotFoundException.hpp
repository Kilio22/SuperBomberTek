/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** SoundNotFoundException
*/

#ifndef SOUNDNOTFOUND_HPP_
#define SOUNDNOTFOUND_HPP_

#include "IndieException.hpp"

namespace Indie::Exceptions
{
    class SoundNotFoundException : public IndieException
    {
        public:
            SoundNotFoundException(const std::string &component, const std::string &message);
            ~SoundNotFoundException() = default;
    };
}

#endif /* !SOUNDNOTFOUND_HPP_ */