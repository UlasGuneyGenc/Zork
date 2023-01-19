#pragma once
#include "Creature.h"

namespace Zork
{
	class Player : public Creature
	{
		Player(const char* name, const char* description);
	};
}