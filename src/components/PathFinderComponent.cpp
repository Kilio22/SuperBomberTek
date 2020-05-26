/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** PathFInderComponent
*/

#include "PathFinderComponent.hpp"
#include "MapComponent.hpp"

void Indie::Components::PathFinderComponent::setPathFinding(irr::core::vector2di aiPosition, int value)
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

void Indie::Components::PathFinderComponent::findPosition(std::array<int, 3> &position)
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
    endPosX = position[0];
    endPosY = position[1];
}

void Indie::Components::PathFinderComponent::getShortlessPath(irr::core::vector2di acPos, irr::core::vector2di nextPos)
{
    int value = (int)map[nextPos.Y][nextPos.X];

    while (map[acPos.Y][acPos.X] != static_cast<OBJECT>(-99)) {
        map[nextPos.Y][nextPos.X] = static_cast<OBJECT>(-99);
        if (map[nextPos.Y + 1][nextPos.X] == static_cast<OBJECT>(value - 1))
            getShortlessPath(irr::core::vector2di(acPos.X, acPos.Y), irr::core::vector2di(nextPos.X, nextPos.Y + 1));
        else if (map[nextPos.Y][nextPos.X + 1] == static_cast<OBJECT>(value - 1))
            getShortlessPath(irr::core::vector2di(acPos.X, acPos.Y), irr::core::vector2di(nextPos.X + 1, nextPos.Y));
        else if (map[nextPos.Y - 1][nextPos.X] == static_cast<OBJECT>(value - 1))
            getShortlessPath(irr::core::vector2di(acPos.X, acPos.Y), irr::core::vector2di(nextPos.X, nextPos.Y - 1));
        else if (map[nextPos.Y][nextPos.X - 1] == static_cast<OBJECT>(value - 1))
            getShortlessPath(irr::core::vector2di(acPos.X, acPos.Y), irr::core::vector2di(nextPos.X, nextPos.Y - 1));
    }
}

irr::core::vector2di Indie::Components::PathFinderComponent::getEndPosition() const
{
    return irr::core::vector2di(endPosX, endPosY);
}

std::vector<std::vector<Indie::Components::OBJECT>> Indie::Components::PathFinderComponent::getMap() const
{
    return map;
}

void Indie::Components::PathFinderComponent::setMap(std::vector<std::vector<OBJECT>> map)
{
    this->map = map;
}