#pragma once

enum class BuffType
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
    case BuffType::FIRE:
        return "Fire";
    case BuffType::EARTH:
        return "Earth";
    case BuffType::WATER:
        return "Water";
    case BuffType::AIR:
        return "Air";
    case BuffType::NONE:
        return "None";
    default:
        return "Invalid Buff Type";
    }
}