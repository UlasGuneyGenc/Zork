#pragma once
#include "Entity.h"

namespace Zork
{
	class Creature : public Entity
	{
	public:
		Creature(const char* name, const char* description);
	};
}
