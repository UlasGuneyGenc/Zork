#include "Item.h"

Item::Item(const char* name, const char* description, Entity* parent, ItemType itemType, BuffType buffType, Stats stats) : Entity(name, description, parent)
{
	this->itemType = itemType;
	this->stats = stats;
	this->buffType = buffType;
}

const ItemType Item::GetItemType() const
{
	return itemType;
}

const Stats Item::GetStats() const
{
	return stats;
}

const BuffType Item::GetBuffType() const
{
	return buffType;
}

const EntityType Item::GetType() const
{
	return EntityType::ITEM;
}
