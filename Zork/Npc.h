#pragma once
#include "Creature.h"

namespace Zork
{
	class Npc : public Creature
	{
	public:
		Npc(const char* name, const char* description, Room* room);
	};
}