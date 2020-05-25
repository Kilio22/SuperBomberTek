/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** SceneNotFound
*/

#ifndef SCENENOTFOUND_HPP_
#define SCENENOTFOUND_HPP_

#include "IndieException.hpp"

namespace Indie::Exceptions
{
    class SceneNotFoundException : public IndieException
    {
        public:
            SceneNotFoundException(const std::string &component, const std::string &message);
            ~SceneNotFoundException() = default;
    };
}

#endif /* !SCENENOTFOUND_HPP_ */
