#pragma once
#include "Direction.h"
#include <string>

std::string directionToString(Direction dir)
{
    switch (dir)
    {
    case Direction::NORTH:
        return "North";
    case Direction::EAST:
        return "East";
    case Direction::SOUTH:
        return "South";
    case Direction::WEST:
        return "West";
    default:
        return "Invalid Direction";
    }
}

