#pragma once
#include "Entity.h"
#include "EntityType.h"
#include "ItemType.h"

class Item : public Entity
{
public:
	Item(const char* name, const char* description, Entity* parent, ItemType itemType);
	const EntityType GetType() const;
};
