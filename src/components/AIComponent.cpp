/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** AIComponent
*/

#include "AIComponent.hpp"

int Indie::Components::AIComponent::setZone(std::vector<std::vector<int>> &map, int initX, int initY, int value)
{
    int rtn = 0;

    if (initX == 0 || initY == 0 || initX >= 100 || initX >= 100 || map[initY][initX] != 0)
        return 0;
    rtn =+ 1;
    map[initY][initX] = value;
    rtn += setZone(map, initX, initY + 1, value);
    rtn += setZone(map, initX + 1, initY, value);
    rtn += setZone(map, initX, initY - 1, value);
    rtn += setZone(map, initX - 1, initY, value);
    this->_dangerZone = rtn;
    return rtn;
}

int Indie::Components::AIComponent::getZone()
{
    return _dangerZone;
}

void Indie::Components::AIComponent::pathFinder(std::vector<std::vector<int>> &map, int initX, int initY, int value)
{
    int canContinue = false;
    map[1][1] = 3; // Position player need to set

    for (int i = 1; i < 15; i++) {
        for (int j = 1; j < 15; j++) {
            if (map[i][j] == value) {
                if (map[i + 1][j] == 0)
                    map[i + 1][j] = value + 1;
                if (map[i][j + 1] == 0)
                    map[i][j + 1] = value + 1;
                if (map[i - 1][j] == 0)
                    map[i - 1][j] = value + 1;
                if (map[i][j - 1] == 0)
                    map[i][j - 1] = value + 1;
                canContinue = true;
            }
        }
    }
    if (canContinue == true)
        pathFinder(map, initX, initY, value + 1);
}

// /*
//     try get Coordonnate where the Ai want to go,
//     Find the most interesting position
//     Find explodable box
// */

// // array : 0 = x , 1 = y, 2 = nbBox;
void Indie::Components::AIComponent::findPosition(std::vector<std::vector<int>> map, int initX, int initY, std::array<int, 3> &position /*std::vector<std::array<int, 3>> banned_position*/) 
{
    int nbBox = 0;
    
    if (initX == 0 || initY == 0 || initX >= 100 || initX >= 100 || map[initY][initX] < 3)
        return;
    if (map[initY + 1][initX] == 1)
        nbBox += 1;
    if (map[initY][initX + 1] == 1)
        nbBox += 1;
    if (map[initY - 1][initX] == 1)
        nbBox += 1;
    if (map[initY][initX - 1] == 1)
        nbBox += 1;
    if (nbBox >= 1 && nbBox > position[2])
        position = {initX, initY, nbBox};
    findPosition(map, initX, initY + 1, position);
    findPosition(map, initX + 1, initY, position);
    // findPosition(map, initX, initY - 1, position);
    // findPosition(map, initX - 1, initY, position);
}

irr::core::vector3df Indie::Components::AIComponent::getNextPosition(int posX, int posY)
{
    irr::core::vector3df nextPosition {posY * 20, 0, posX * 20};
    return nextPosition;
}

void Indie::Components::AIComponent::setNextDirection(std::vector<std::vector<int>> &map, int posX, int posY)
{
    _nextX = posX;
    _nextY = posY;

    map[posY][posX] = 0;
    if (map[posY + 1][posX] == -99) {
        setDirection(UP);
        _nextY += 1;
    }
    if (map[posY][posX + 1] == -99) {
        setDirection(RIGHT);
        _nextX += 1;
    }
    if (map[posY - 1][posX] == -99) {
        setDirection(DOWN);
        _nextY -= 1;
    }
    if (map[posY][posX - 1] == -99) {
        setDirection(LEFT);
        _nextX -= 1;
    }
}

bool Indie::Components::AIComponent::hasArrived(std::vector<std::vector<int>> &map) const
{
    return map[_endY][_endX] != -99 ? true : false;
}

int Indie::Components::AIComponent::getNextXDirection() const
{
    return _nextX;
}

int Indie::Components::AIComponent::getNextYDirection() const
{
    return _nextY;
}

void Indie::Components::AIComponent::setDirection(enum Indie::Components::AIComponent::Direction direction)
{
    _direction = direction;
}

enum Indie::Components::AIComponent::Direction Indie::Components::AIComponent::getDirection() const
{
    return _direction;
}

bool Indie::Components::AIComponent::isMoving(enum Direction direction)
{
    return (_direction == direction) ? true : false;
}

std::vector<std::vector<int>> Indie::Components::AIComponent::getMap() const
{
    //return this->_mapGenerator.getMap();
}

bool Indie::Components::AIComponent::hasMoved(irr::core::vector3df position, irr::core::vector3df nextPosition)
{
    if (_direction == UP && position.Y < nextPosition.Y)
        return false;
    if (_direction == DOWN && position.Y > nextPosition.Y)
        return false;
    if (_direction == RIGHT && position.X < nextPosition.X)
        return false;
    if (_direction == DOWN && position.X > nextPosition.X)
        return false;
    setDirection(NONE);
    return true;

}

void Indie::Components::AIComponent::getShortlessPath(std::vector<std::vector<int>> &map, int initX, int initY, int futurX, int futurY)
{ 
    int value = map[futurY][futurX];

    while (map[initY][initX] != -99) {
        map[futurY][futurX] = -99;
        if (map[futurY + 1][futurX] == value - 1)
            getShortlessPath(map, initX, initY, futurX, futurY + 1);
        else if (map[futurY][futurX + 1] == value - 1)
            getShortlessPath(map, initX, initY, futurX + 1, futurY);
        else if (map[futurY - 1][futurX] == value - 1)
            getShortlessPath(map, initX, initY, futurX, futurY - 1);
        else if (map[futurY][futurX - 1] == value - 1)
            getShortlessPath(map, initX, initY, futurX, futurY - 1);
    }
}
