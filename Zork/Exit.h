#pragma once
#include "Entity.h"
#include "Direction.h"

namespace Zork
{
	class Room;
	class Exit : public Entity
	{
	public:
		Exit(const char* name, const char* description, Direction direction, Room* origin, Room* destination);
	};
}
