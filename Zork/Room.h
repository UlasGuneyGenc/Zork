#pragma once
#include "Entity.h"

namespace Zork
{
	class Room : public Entity
	{
		Room(const char* name, const char* description);
	};
}