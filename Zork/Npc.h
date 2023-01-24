#pragma once
#include "Creature.h"

class Npc : public Creature
{
public:
	Npc(const char* name, const char* description, Room* room, BuffType buffType, Stats* stats);
	virtual const EntityType GetType() const;
	BuffType buffType;

};
