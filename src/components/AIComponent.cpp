/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** AIComponent
*/

#include "AIComponent.hpp"
#include <iostream>

// int Indie::Components::AIComponent::setZone(std::vector<std::vector<OBJECT>> &map, int acPos.X, int initY, int value)
// {
//     int rtn = 0;

//     if (acPos.X == 0 || initY == 0 || acPos.X >= 100 || acPos.X >= 100 || map[initY][acPos.X] != 0)
//         return 0;
//     rtn =+ 1;
//     map[initY][acPos.X] = value;
//     rtn += setZone(map, acPos.X, initY + 1, value);
//     rtn += setZone(map, acPos.X + 1, initY, value);
//     rtn += setZone(map, acPos.X, initY - 1, value);
//     rtn += setZone(map, acPos.X - 1, initY, value);
//     this->_dangerZone = rtn;
//     return rtn;
// }

// int Indie::Components::AIComponent::getZone()
// {
//     return _dangerZone;
// }

void Indie::Components::AIComponent::setPathFinding(std::vector<std::vector<OBJECT>> &map, irr::core::vector2di aiPosition, int value)
{
    bool canContinue = true;
    map[aiPosition.Y][aiPosition.X] = static_cast<OBJECT>(4);

    while (canContinue == true) {
        canContinue = false;
        for (int i = 1; i < 15; i++) {
            for (int j = 1; j < 15; j++) {
                if (map[i][j] == static_cast<OBJECT>(value)) {
                    map[i + 1][j] = (map[i + 1][j] == static_cast<OBJECT>(0)) ? static_cast<OBJECT>(value + 1) : map[i + 1][j];
                    map[i][j + 1] = (map[i][j + 1] == static_cast<OBJECT>(0)) ? static_cast<OBJECT>(value + 1) : map[i][j + 1];
                    map[i - 1][j] = (map[i - 1][j] == static_cast<OBJECT>(0)) ? static_cast<OBJECT>(value + 1) : map[i - 1][j];
                    map[i][j - 1] = (map[i][j - 1] == static_cast<OBJECT>(0)) ? static_cast<OBJECT>(value + 1) : map[i][j - 1];
                    canContinue = true;
                }
            }
        }
        value++;
    }
}

void Indie::Components::AIComponent::findPosition(std::vector<std::vector<OBJECT>> &map, std::array<int, 3> &position)
{
    int nbBox = 0;

    for (int i = 1; i < 15; i++) {
        for (int j = 1; j < 15; j++) {
            nbBox = 0;
            if (map[j][i] >= static_cast<OBJECT>(4)) {
                nbBox += (map[j + 1][i] == OBJECT::BOX) ? 1 : 0;
                nbBox += (map[j][i + 1] == OBJECT::BOX) ? 1 : 0;
                nbBox += (map[j - 1][i] == OBJECT::BOX) ? 1 : 0;
                nbBox += (map[j][i - 1] == OBJECT::BOX) ? 1 : 0;
                if (nbBox >= 1 && nbBox > position[2])
                    position = {i, j, nbBox};
            }
        }
    }
    _endX = position[0];
    _endY = position[1];
}

void Indie::Components::AIComponent::setNextDirection(std::vector<std::vector<OBJECT>> &map, int posX, int posY)
{
    _nextX = posX;
    _nextY = posY;

    map[posY][posX] = static_cast<OBJECT>(0);
    if (map[posY + 1][posX] == static_cast<OBJECT>(-99)) {
        setDirection(Indie::Components::DIRECTION::UP);
        _nextY += 1;
        return;
    }
    if (map[posY][posX + 1] == static_cast<OBJECT>(-99)) {
        setDirection(Indie::Components::DIRECTION::RIGHT);
        _nextX += 1;
        return;
    }
    if (map[posY - 1][posX] == static_cast<OBJECT>(-99)) {
        setDirection(Indie::Components::DIRECTION::DOWN);
        _nextY -= 1;
        return;
    }
    if (map[posY][posX - 1] == static_cast<OBJECT>(-99)) {
        setDirection(Indie::Components::DIRECTION::LEFT);
        _nextX -= 1;
        return;
    }
}

bool Indie::Components::AIComponent::hasArrived(std::vector<std::vector<OBJECT>> &map) const
{
    return map[_endY][_endX] == static_cast<OBJECT>(-99) ? true : false;
}

int Indie::Components::AIComponent::getNextXDirection() const
{
    return _nextX;
}

int Indie::Components::AIComponent::getNextYDirection() const
{
    return _nextY;
}

void Indie::Components::AIComponent::setDirection(Indie::Components::DIRECTION direction)
{
    _direction = direction;
}

Indie::Components::DIRECTION Indie::Components::AIComponent::getDirection() const
{
    return _direction;
}

bool Indie::Components::AIComponent::isMoving(Indie::Components::DIRECTION direction)
{
    return (_direction == direction);
}

bool Indie::Components::AIComponent::hasMoved(irr::core::vector3df position, irr::core::vector3df nextPosition)
{
    if (_direction == Indie::Components::DIRECTION::UP && position.Z < nextPosition.Z)
        return false;
    if (_direction == Indie::Components::DIRECTION::DOWN && position.Z > nextPosition.Z)
        return false;
    if (_direction == Indie::Components::DIRECTION::RIGHT && position.X < nextPosition.X)
        return false;
    if (_direction == Indie::Components::DIRECTION::LEFT && position.X > nextPosition.X)
        return false;
    setDirection(Indie::Components::DIRECTION::NONE);
    return true;
}

void Indie::Components::AIComponent::getShortlessPath(std::vector<std::vector<OBJECT>> &map, irr::core::vector2di acPos, irr::core::vector2di nextPos)
{
    int value = (int)map[nextPos.Y][nextPos.X];

    while (map[acPos.Y][acPos.X] != static_cast<OBJECT>(-99)) {
        map[nextPos.Y][nextPos.X] = static_cast<OBJECT>(-99);
        if (map[nextPos.Y + 1][nextPos.X] == static_cast<OBJECT>(value - 1))
            getShortlessPath(map, irr::core::vector2di(acPos.X, acPos.Y), irr::core::vector2di(nextPos.X, nextPos.Y + 1));
        else if (map[nextPos.Y][nextPos.X + 1] == static_cast<OBJECT>(value - 1))
            getShortlessPath(map, irr::core::vector2di(acPos.X, acPos.Y), irr::core::vector2di(nextPos.X + 1, nextPos.Y));
        else if (map[nextPos.Y - 1][nextPos.X] == static_cast<OBJECT>(value - 1))
            getShortlessPath(map, irr::core::vector2di(acPos.X, acPos.Y), irr::core::vector2di(nextPos.X, nextPos.Y - 1));
        else if (map[nextPos.Y][nextPos.X - 1] == static_cast<OBJECT>(value - 1))
            getShortlessPath(map, irr::core::vector2di(acPos.X, acPos.Y), irr::core::vector2di(nextPos.X, nextPos.Y - 1));
    }
}