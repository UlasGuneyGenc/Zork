#include "Creature.h"

Creature::Creature(const char* name, const char* description, Room* room) : Entity(name, description, (Entity*)room)
{
}

const Room* Creature::GetRoom() const
{
	if (GetParent()->GetType() == EntityType::ROOM)
	{
		return (Room*)GetParent();
	}
	return nullptr;
}

