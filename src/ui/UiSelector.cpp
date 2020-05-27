/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** UiSelector
*/

#include "UiSelector.hpp"

Indie::UiSelector::UiSelector(int sizeX, int sizeY, irr::EKEY_CODE up, irr::EKEY_CODE down, irr::EKEY_CODE left, irr::EKEY_CODE right)
: posX(0), posY(0), sizeX(sizeX), sizeY(sizeY), up(up), down(down), left(left), right(right)
{
}

Indie::UiSelector::~UiSelector()
{}

std::pair<int, int> Indie::UiSelector::getPos() const
{
    return std::pair<int, int>(posX, posY);
}

void Indie::UiSelector::update()
{
    if (EventHandler::getInstance().isKeyPressedAtOnce(up))
        posY = (posY >= 1) ? posY - 1 : posY;
    if (EventHandler::getInstance().isKeyPressedAtOnce(left))
        posX = (posX >= 1) ? posX - 1 : posX;
    if (EventHandler::getInstance().isKeyPressedAtOnce(down))
        posY = (posY < sizeY - 1) ? posY + 1: posY;
    if (EventHandler::getInstance().isKeyPressedAtOnce(right))
        posX = (posX < sizeX - 1) ? posX + 1: posX;
    EventHandler::getInstance().resetKeysStatusOnce();
}

void Indie::UiSelector::setPos(int posX, int posY)
{
    this->posX = posX;
    this->posY = posY;
}