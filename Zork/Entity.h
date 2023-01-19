#pragma once
#include <string>
#include <list>

namespace Zork
{
	enum EntityType
	{
		ENTITY,
		CREATURE,
		EXIT,
		ITEM,
		ROOM,
		PLAYER,
		NPC
	};

	class Entity
	{
		

	public:
		Entity(const char* name, const char* description);
		EntityType type;
		std::string name;
		std::string description;
		std::list<Entity*> entities;
	};
}