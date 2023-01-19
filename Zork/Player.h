#pragma once
#include "Creature.h"

namespace Zork
{
	class Player : public Creature
	{
	public:
		Player(const char* name, const char* description, Room* room);
	};
}