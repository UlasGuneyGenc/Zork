#pragma once
#include "Entity.h"
#include "Direction.h"

class Room;
class Exit : public Entity
{
public:
	Exit(const char* name, const char* description, Direction direction, Room* origin, Room* destination);
	virtual const EntityType GetType() const;
	virtual const Direction GetDirection() const;
	const Room* GetDestinationRoom() const;

	void Look() const;
	bool locked;
private:
	Direction direction;
	Room* origin;
	Room* destination;
};
