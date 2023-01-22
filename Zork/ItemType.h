#pragma once
#include <string>

enum ItemType
{
	KEY,
	WEAPON,
	ARMOR,
    STORAGE,
    
};

inline const char* ItemTypeToString(const ItemType itemType)
{
    switch (itemType)
    {
    case ItemType::KEY:
        return "Key";
    case ItemType::WEAPON:
        return "Weapon";
    case ItemType::ARMOR:
        return "Armor";
    case ItemType::STORAGE:
        return "Storage";
    default:
        return "None";
    }
}
