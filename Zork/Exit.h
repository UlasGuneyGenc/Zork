#pragma once
#include "Entity.h"
#include "Direction.h"
#include "Item.h"

class Room;
class Exit : public Entity
{
public:
	Exit(const char* name, const char* description, Direction direction, Room* origin, Room* destination, bool locked, Item* key);
	const EntityType GetType() const;
	const Direction GetDirection() const;
	Room* GetDestinationRoom() const;
	const Item* GetKey() const;
	void Unlock();
	bool IsLocked();
	void Look() const;

private:
	Direction direction;
	bool locked;
	Item* key;
	Room* origin;
	Room* destination;
};
