#include "Room.h"
#include <iostream>
#include "Exit.h"
#include "Helpers.h"

Room::Room(const char* name, const char* description) : Entity(name, description, NULL)
{
}

void Room::Look() const
{
    std::cout << std::endl << "You are in " << name << ". " << description << std::endl;

    //Get all exits and print them
    for (const auto& child : GetChildren()) {
        if (child->GetType() != EntityType::EXIT) {
            continue;
        }
        const Exit* ex = static_cast<const Exit*>(child);
        std::cout << "\nAt the direction " << directionToString(ex->GetDirection())
            << " you see an exit to " << ex->GetDestinationRoom()->name << "\n";
    }
}

const EntityType Room::GetType() const
{
	return EntityType::ROOM;
}
