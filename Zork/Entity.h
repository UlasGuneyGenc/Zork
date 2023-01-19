#pragma once
#include <string>
#include <list>
#include "EntityType.h"

namespace Zork
{
	class Entity
	{
		
	public:
		Entity(const char* name, const char* description, Entity* parent);
		EntityType type;
		std::string name;
		std::string description;
		Entity* parent;
		std::list<Entity*> entities;
	};
}