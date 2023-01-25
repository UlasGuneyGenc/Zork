#pragma once

enum class Direction
{
	NORTH,
	EAST,
	SOUTH,
	WEST,
    INVALID
};

inline const char* DirectionToString(Direction dir)
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

inline Direction StringToDirection(const std::string& str) {
    if (str == "north") {
        return Direction::NORTH;
    }
    else if (str == "east") {
        return Direction::EAST;
    }
    else if (str == "south") {
        return Direction::SOUTH;
    }
    else if (str == "west") {
        return Direction::WEST;
    }
    else {
        return Direction::INVALID;
    }
}