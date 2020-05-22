/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** FileNotFoundException
*/

#ifndef FILENOTFOUNDEXCEPTION_HPP_
#define FILENOTFOUNDEXCEPTION_HPP_

#include "IndieException.hpp"

namespace Indie::Exceptions
{
    class FileNotFoundException : public IndieException
    {
        public:
            FileNotFoundException(const std::string &component, const std::string &message);
            ~FileNotFoundException() = default;

        protected:
        private:
    };
}

#endif /* !FILENOTFOUNDEXCEPTION_HPP_ */
