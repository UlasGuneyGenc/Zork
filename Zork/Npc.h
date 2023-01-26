#pragma once
#include "Creature.h"

class Npc : public Creature
{
public:
	Npc(const char* name, const char* description, Room* room, BuffType buffType, Stats* stats, bool isLastBoss);
	const EntityType GetType() const override;
	bool GetIsLastBoss();
	BuffType buffType;
	
private:
	bool isLastBoss;
};
