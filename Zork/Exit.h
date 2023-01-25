#pragma once
#include "Entity.h"
#include "Direction.h"
#include "Item.h"

class Room;
class Exit : public Entity
{
public:
	Exit(const char* name, const char* description, Direction direction, Room* origin, Room* destination, bool locked, Item* key);
	virtual const EntityType GetType() const;
	virtual const Direction GetDirection() const;
	const Room* GetDestinationRoom() const;
	const Item* GetKey() const;
	const void Unlock() const;
	mutable bool locked;

private:
	Direction direction;
	Item* key;
	Room* origin;
	Room* destination;
};
