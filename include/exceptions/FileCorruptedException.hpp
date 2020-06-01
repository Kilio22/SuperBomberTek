/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** FileCorruptedException | Author: Kylian BALAN - kylian.balan@epitech.eu
*/

#ifndef FILECORRUPTEDEXCEPTION_HPP_
#define FILECORRUPTEDEXCEPTION_HPP_

#include "IndieException.hpp"

namespace Indie::Exceptions
{
    class FileCorruptedException : public IndieException
    {
        public:
        FileCorruptedException(const std::string &component, const std::string &message);
        ~FileCorruptedException() = default;
    };
} // namespace Indie::Exceptions

#endif /* !FILECORRUPTEDEXCEPTION_HPP_ */
