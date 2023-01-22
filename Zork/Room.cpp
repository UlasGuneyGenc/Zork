#include "Room.h"
#include "Exit.h"
#include "Direction.h"
#include <iostream>

Room::Room(const char* name, const char* description) : Entity(name, description, NULL)
{
}

void Room::Look() const
{
    std::cout << "You are in " << name << ". " << description << std::endl;

    //Get all exits and print them
    for (const auto& child : GetChildren()) {
        if (auto ex = dynamic_cast<const Exit*>(child)) {
            std::cout << "\nAt the direction " << DirectionToString(ex->GetDirection())
                << " you see an exit to " << ex->GetDestinationRoom()->name << ".";
        }
    }
    std::cout << "\n";
}

const Exit* Room::GetExit(Direction direction) const
{
    if (direction == Direction::INVALID)
    {
        std::cout << "There is no exit with that name!" << std::endl;
        return nullptr;
    }

    //Search exits for appropiate direction
    for (const auto& child : GetChildren()) {
        if (auto ex = dynamic_cast<const Exit*>(child)) {
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

