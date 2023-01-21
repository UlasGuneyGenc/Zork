#include "Room.h"
#include <iostream>
#include "Exit.h"

Room::Room(const char* name, const char* description) : Entity(name, description, NULL)
{
}

void Room::Look() const
{
    std::cout << std::endl << "You are in " << name << ". " << description << std::endl;

    //Get all exits and print them
    for (const auto& child : GetChildren()) {
        if (auto ex = dynamic_cast<const Exit*>(child)) {
            std::cout << "\nAt the direction " << DirectionToString(ex->GetDirection())
                << " you see an exit to " << ex->GetDestinationRoom()->name << "\n";
        }
    }
}

const EntityType Room::GetType() const
{
	return EntityType::ROOM;
}
