#pragma once
#include "Entity.h"
#include "Exit.h"

class Room : public Entity
{
public:
	Room(const char* name, const char* description);
	void Look() const;
	const Exit* GetExit(Direction direction) const;
	const EntityType GetType() const;

};
