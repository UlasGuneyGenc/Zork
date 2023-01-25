#include <iostream>
#include <vector>
#include "Room.h"
#include "Exit.h"
#include "Direction.h"
#include "Item.h"
#include "Npc.h"

Room::Room(const char* name, const char* description) : Entity(name, description, NULL)
{
}

void Room::Look() const
{
    std::cout << "You are in " << name << ". " << description << std::endl << std::endl;
    const std::list<Entity*>& allChildren = GetChildren();
    std::vector<const Item*> items;
    items.reserve(allChildren.size());

    for (const auto& child : allChildren) {
        switch (child->GetType()) {
        case EntityType::EXIT:
            std::cout << "At the direction " << DirectionToString(static_cast<Exit*>(child)->GetDirection())
                << " you see an exit to " << static_cast<Exit*>(child)->GetDestinationRoom()->name << "." << std::endl;
            break;
        case EntityType::ITEM:
            items.push_back(static_cast<Item*>(child));
            break;
        case EntityType::NPC:
            std::cout << "There is a monster called '" << child->name << "' in the room." << std::endl << std::endl;
            break;
        }
    }
    if (!items.empty()) {
        std::cout << "\nThere are following items in the room:" << std::endl;
        for (const auto& item : items) {
            std::cout << item->name << std::endl;
        }
    }
}

Exit* Room::GetExit(Direction direction) const
{
    if (direction == Direction::INVALID)
    {
        std::cout << "There is no exit with that name!" << std::endl;
        return nullptr;
    }

    //Search exits for appropiate direction
    for (const auto& child : GetChildren()) {
        if (child->GetType() == EntityType::EXIT)
        {
            Exit* ex = static_cast<Exit*>(child);
            if (ex->GetDirection() == direction)
            {
                return ex;
            }
        }
    }

    //no exit is found
    std::cout << "No exit was found in that direction." << std::endl;
    return nullptr;
}

const EntityType Room::GetType() const
{
	return EntityType::ROOM;
}

