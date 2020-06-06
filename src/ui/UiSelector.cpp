/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** UiSelector
*/

#include "UiSelector.hpp"
#include "ServiceLocator.hpp"

Indie::UiSelector::UiSelector(int sizeX, int sizeY, irr::EKEY_CODE up, irr::EKEY_CODE down, irr::EKEY_CODE left, irr::EKEY_CODE right)
: posX(0), posY(0), sizeX(sizeX), sizeY(sizeY), up(up), down(down), left(left), right(right), soundX(true), soundY(true)
{
}

Indie::UiSelector::UiSelector(int sizeX, int sizeY, irr::EKEY_CODE up, irr::EKEY_CODE down, irr::EKEY_CODE left, irr::EKEY_CODE right, bool soundX, bool soundY)
: posX(0), posY(0), sizeX(sizeX), sizeY(sizeY), up(up), down(down), left(left), right(right), soundX(soundX), soundY(soundY)
{
}

Indie::UiSelector::~UiSelector()
{}

std::pair<int, int> Indie::UiSelector::getPos() const
{
    return std::pair<int, int>(posX, posY);
}

void Indie::UiSelector::setBLockSound(bool x, bool y)
{
    soundX = x;
    soundY = y;
}

void Indie::UiSelector::update()
{
    if (EventHandler::getInstance().isKeyPressedAtOnce(up)) {
        if (posY >= 1) {
            posY = posY - 1;
            ServiceLocator::getInstance().get<SoundManager>().playSound("menu_move");
        } else if (soundY) {
            ServiceLocator::getInstance().get<SoundManager>().playSound("menu_lock");
        }
    }
    if (EventHandler::getInstance().isKeyPressedAtOnce(left)) {
        if (posX >= 1) {
            posX = posX - 1;
            ServiceLocator::getInstance().get<SoundManager>().playSound("menu_move");
        } else if (soundX) {
            ServiceLocator::getInstance().get<SoundManager>().playSound("menu_lock");
        }
    }
    if (EventHandler::getInstance().isKeyPressedAtOnce(down)) {
        if (posY < sizeY - 1) {
            posY = posY + 1;
            ServiceLocator::getInstance().get<SoundManager>().playSound("menu_move");
        } else if (soundY) {
            ServiceLocator::getInstance().get<SoundManager>().playSound("menu_lock");
        }
    }
    if (EventHandler::getInstance().isKeyPressedAtOnce(right)) {
        if (posX < sizeX - 1) {
            posX = posX + 1;
            ServiceLocator::getInstance().get<SoundManager>().playSound("menu_move");
        } else if (soundX) {
            ServiceLocator::getInstance().get<SoundManager>().playSound("menu_lock");
        }
    }
}

void Indie::UiSelector::setPos(int posX, int posY)
{
    this->posX = posX;
    this->posY = posY;
}

void Indie::UiSelector::setSize(int sizeX, int sizeY)
{
    this->sizeX = sizeX;
    this->sizeY = sizeY;
    if (posX >= sizeX)
        posX = sizeX - 1;
    if (posY >= sizeY)
        posY = sizeY - 1;
}