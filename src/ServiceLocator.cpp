/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** SceneLocator
*/

#include "ServiceLocator.hpp"

MusicManager ServiceLocator::musicManager;
SceneManager ServiceLocator::sceneManager;

void ServiceLocator::drop()
{
    musicManager.drop();
    sceneManager.drop();
}