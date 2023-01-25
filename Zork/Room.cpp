#include "Room.h"
#include "Exit.h"
#include "Direction.h"
#include <iostream>
#include "Item.h"
#include <vector>
#include "Npc.h"

Room::Room(const char* name, const char* description) : Entity(name, description, NULL)
{
}

void Room::Look() const
{
    std::cout << "You are in " << name << ". " << description << std::endl << std::endl;
    const std::list<Entity*>& all_children = GetChildren();

    //Get all exits and print them
    for (const auto& child : GetChildren()) {
        if (child->GetType() == EntityType::EXIT)
        {
            Exit* ex = static_cast<Exit*>(child);
            std::cout << "At the direction " << DirectionToString(ex->GetDirection())
                << " you see an exit to " << ex->GetDestinationRoom()->name << "." << std::endl;
        }
    }

    //Get all the items
    std::vector<const Item*> items;
    items.reserve(all_children.size());
    for (const auto& child : all_children) {
        if (auto item = dynamic_cast<const Item*>(child)) {
            items.push_back(item);
        }
    }
    //Print the items if there are any
    if (!items.empty()) {
        std::cout << "\nThere are following items in the room:" << std::endl;
        for (const auto& item : items) {
            std::cout << item->name << std::endl;
        }
    }

    //Get the monsters and display them
    for (const auto& child : GetChildren()) {
        if (auto monster = dynamic_cast<const Npc*>(child)) {
            std::cout << "There is a monster called '"<< monster->name <<"' in the room." << std::endl;

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

