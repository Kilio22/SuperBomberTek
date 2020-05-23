/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** SceneManagerException
*/

#ifndef SCENEMANAGEREXCEPTION_HPP_
#define SCENEMANAGEREXCEPTION_HPP_

#include "IndieException.hpp"

namespace Indie::Exceptions
{
    class SceneManagerException : public IndieException
    {
        public:
            SceneManagerException(const std::string &component, const std::string &message);
            ~SceneManagerException() = default;
    };
}

#endif /* !SCENEMANAGEREXCEPTION_HPP_ */
