#include "Npc.h"

Npc::Npc(const char* name, const char* description, Room* room, BuffType buffType, Stats* stats, bool isLastBoss) : Creature(name, description, room, stats)
{
	this->buffType = buffType;
	this->isLastBoss = isLastBoss;
}

const EntityType Npc::GetType() const
{
	return EntityType::NPC;
}

bool Npc::GetIsLastBoss()
{
	return isLastBoss;
}
