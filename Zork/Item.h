#pragma once
#include "Entity.h"
#include "EntityType.h"
#include "ItemType.h"
#include "Stats.h"
#include "BuffType.h"

class Item : public Entity
{
public:
	Item(const char* name, const char* description, Entity* parent, ItemType itemType, BuffType buffType, Stats stat);
	const EntityType GetType() const;
	const ItemType GetItemType() const;
	const Stats GetStats() const;
	const BuffType GetBuffType() const;


private:
	ItemType itemType;
	BuffType buffType;
	Stats stats;
};
