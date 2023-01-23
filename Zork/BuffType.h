#pragma once

enum BuffType
{
	FIRE,
	EARTH,
	WATER,
	AIR,
	NONE
};

inline const char* BuffTypeToString(BuffType type)
{
    switch (type)
    {
    case FIRE:
        return "Fire";
    case EARTH:
        return "Earth";
    case WATER:
        return "Water";
    case AIR:
        return "Air";
    case NONE:
        return "None";
    default:
        return "Invalid Buff Type";
    }
}