#pragma once
#include "Entity.h"

class Room : public Entity
{
public:
	Room(const char* name, const char* description);
	void Look() const;
	const EntityType GetType() const;
};
