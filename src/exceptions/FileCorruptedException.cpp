/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** FileCorruptedException | Author: Kylian BALAN - kylian.balan@epitech.eu
*/

#include "FileCorruptedException.hpp"

Indie::Exceptions::FileCorruptedException::FileCorruptedException(const std::string &component, const std::string &message)
    : IndieException(component, message)
{
}
