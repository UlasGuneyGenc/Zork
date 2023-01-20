#include "Exit.h"
#include "Room.h"
#include <iostream>

Exit::Exit(const char* name, const char* description, Direction direction, Room* origin, Room* destination)
	: Entity(name, description, (Entity*) origin )
{
	this->direction = direction;
	this->origin = origin;
	this->destination = destination;
	locked = true;
}

const EntityType Exit::GetType() const
{
	return EntityType::EXIT;
}

const Direction Exit::GetDirection() const
{
	return direction;
}

const Room* Exit::GetDestinationRoom() const
{
	return destination;
}

void Exit::Look() const
{
	std::cout << (locked ? "Exit is locked. " : "It leads to ") << destination->name << ". " << description << std::endl;
}
