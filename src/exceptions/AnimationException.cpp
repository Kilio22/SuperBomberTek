/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** AnimationException | Author: Kylian BALAN - kylian.balan@epitech.eu
*/

#include "AnimationException.hpp"

Indie::Exceptions::AnimationException::AnimationException(const std::string &component, const std::string &message)
    : IndieException(component, message)
{
}
