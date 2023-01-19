#pragma once
#include "Entity.h"

namespace Zork
{
	class Item : public Entity
	{
		Item(const char* name, const char* description);
	};
}