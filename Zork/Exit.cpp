#include "Exit.h"
#include "Room.h"
#include <iostream>

Exit::Exit(const char* name, const char* description, Direction direction, Room* origin, Room* destination, bool locked, Item* key)
	: Entity(name, description, (Entity*) origin )
{
	this->direction = direction;
	this->origin = origin;
	this->destination = destination;
	this->locked = locked;
	this->key = key;
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

const Item* Exit::GetKey() const
{
	return key;
}

const void Exit::Unlock() const
{
	locked = false;
}


