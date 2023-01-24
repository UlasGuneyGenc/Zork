#include "Npc.h"

Npc::Npc(const char* name, const char* description, Room* room, BuffType buffType, Stats* stats) : Creature(name, description, room, stats)
{
	this->buffType = buffType;
}

const EntityType Npc::GetType() const
{
	return EntityType::NPC;
}
