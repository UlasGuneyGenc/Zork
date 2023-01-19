#pragma once
#include <string>
#include <list>
#include "EntityType.h"

class Entity
{		
public:
	Entity(const char* name, const char* description, Entity* parent);
	void Insert(Entity* child);
	void Remove(Entity* child);
	EntityType type;
	std::string name;
	std::string description;
	Entity* parent;
	std::list<Entity*> entities;
};
