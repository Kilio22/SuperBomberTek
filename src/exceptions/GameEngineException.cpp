/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** GameEngineException
*/

#include "GameEngineException.hpp"

Indie::Exceptions::GameEngineException::GameEngineException(const std::string &component, const std::string &message)
    : IndieException(component, message)
{
}
