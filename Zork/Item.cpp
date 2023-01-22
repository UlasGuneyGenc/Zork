#include "Item.h"

Item::Item(const char* name, const char* description, Entity* parent, ItemType itemType) : Entity(name, description, parent)
{
}

const EntityType Item::GetType() const
{
	return EntityType::ITEM;
}
