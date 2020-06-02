/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** AnimationException | Author: Kylian BALAN - kylian.balan@epitech.eu
*/

#ifndef ANIMATIONEXCEPTION_HPP_
#define ANIMATIONEXCEPTION_HPP_

#include "IndieException.hpp"

namespace Indie::Exceptions
{
    class AnimationException : public IndieException
    {
        public:
        AnimationException(const std::string &component, const std::string &message);
        ~AnimationException() = default;
    };
} // namespace Indie::Exceptions

#endif /* !ANIMATIONEXCEPTION_HPP_ */
