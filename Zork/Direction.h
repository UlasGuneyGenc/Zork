#pragma once

enum Direction
{
	NORTH,
	EAST,
	SOUTH,
	WEST
};

inline const char* DirectionToString(const Direction dir)
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