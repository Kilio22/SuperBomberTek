/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** GameEngineException
*/

#ifndef GAMEENGINEEXCEPTION_HPP_
#define GAMEENGINEEXCEPTION_HPP_

#include "IndieException.hpp"

namespace Indie::Exceptions
{
    class GameEngineException : public IndieException
    {
        public:
            GameEngineException(const std::string &component, const std::string &message) : IndieException(component, message) {}
            ~GameEngineException() = default;

        protected:
        private:
    };
}

#endif /* !GAMEENGINEEXCEPTION_HPP_ */
