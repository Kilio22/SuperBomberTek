/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** IndieException
*/

#ifndef INDIEEXCEPTION_HPP_
#define INDIEEXCEPTION_HPP_

#include <exception>
#include <string>

#define __ERROR_STR(f, l, fu) (#f " at line " #l "(" #fu ")")
#define _ERROR_STR(f, l, fu) __ERROR_STR(f, l, fu)
#define ERROR_STR _ERROR_STR(__FILE__, __LINE__, __func__)

namespace Indie::Exceptions
{
    class IndieException : public std::exception
    {
    public:
        IndieException(const std::string &component, const std::string &message);
        virtual ~IndieException() = default;

        /**
         * @brief Returns a C-style character string describing the general cause of the current error.
         * @return const char* The string
         */
        const char *what() const noexcept final;

        /**
         * @brief Gets the component where the exception has been thrown
         * @return const std::string& The component's name
         */
        const std::string &getComponent(void) const noexcept;

    private:
        std::string _component;
        std::string _message;
    };
} // namespace Indie::Exceptions

#endif /* !INDIEEXCEPTION_HPP_ */