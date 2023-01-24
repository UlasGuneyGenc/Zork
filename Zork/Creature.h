#pragma once
#include "Entity.h"
#include "Room.h"
#include "Item.h"
#include "BuffType.h"
#include "Stats.h"

class Creature : public Entity
{
public:
	Creature(const char* name, const char* description, Room* room, BuffType buffType, Stats* stats);
	const Room* GetRoom() const;
	virtual void Update();
	virtual const EntityType GetType() const;
	virtual void GetInfo() const;
	void CalculateStat();

protected:
	Item* buffItem;
	Item* weapon;
	Item* armor;
	Stats* stats;
	int currentHealth;
};
