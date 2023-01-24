#include "Player.h"
#include "Exit.h"
#include "Direction.h"
#include <iostream>
#include "Item.h"
#include "Stats.h"


Player::Player(const char* name, const char* description, Room* room, BuffType buffType, Stats* stats) : Creature(name, description, room, buffType, stats)
{
}

void Player::Look() const
{
	GetParent()->Look();
}

void Player::Update()
{
}

void Player::Move(const std::vector<std::string>& arguments)
{
	const Exit* wantedExit = GetRoom()->GetExit(StringToDirection(arguments[1]));
	if (wantedExit != NULL)
	{
		ChangeParent((Entity*)wantedExit->GetDestinationRoom());
		GetParent()->Look();
	}
}

void Player::Take(const std::vector<std::string>& arguments)
{
	switch (arguments.size()) {
	case 2:
	{
		Item* item = (Item*)(GetParent()->Find(arguments[1], EntityType::ITEM));
		if (item == nullptr)
		{
			std::cout << "There is no item named '" << arguments[1] << "' in the current room." << std::endl;
			return;
		}
		item->ChangeParent(this);
		std::cout << "You took the '" << item->name << "'." << std::endl;
		break;
	}
	case 4:
	{
		Entity* entity = (Item*)(GetParent()->Find(arguments[3], EntityType::ITEM));
		if (entity == nullptr)
		{
			std::cout << "There is no such thing as '" << arguments[1] << "'" << std::endl;
			return;
		}
		if (entity->GetType() == EntityType::ITEM)
		{
			Item* childItem = (Item*)(entity->Find(arguments[1], EntityType::ITEM));
			if (childItem == nullptr)
			{
				std::cout << "There is no item named '" << arguments[1] << "' in the " << "'" << entity->name << "'" << std::endl;
				return;
			}
			childItem->ChangeParent(this);
			std::cout << "You took the '" << childItem->name << "' from '" << entity->name << "'" << std::endl;
		}
		break;
	}
	default:
		break;
	}
}

void Player::Drop(const std::vector<std::string>& arguments)
{
	Item* item = (Item*)(Find(arguments[1], EntityType::ITEM));
	if (item == nullptr)
	{
		std::cout << "There is no item named '" << arguments[1] << "' in your bag." << std::endl;
		return;
	}

	item->ChangeParent((Entity*)GetRoom());

	if (item == weapon)
	{
		weapon = nullptr;
		CalculateStat();
	}
	else if (item == armor)
	{
		armor = nullptr;
		CalculateStat();
	}
	else if (item == buffItem)
	{
		buffItem = nullptr;
		CalculateStat();
	}

	std::cout << "You dropped the '" << item->name << "'." << std::endl;
}

void Player::Examine(const std::vector<std::string>& arguments)
{
	//we return message because input is not enough for what to examine
	if (arguments.size()<=1)
	{
		std::cout << "You need to give me more details!" << std::endl;
		return;
	}

	//Try to find the thing we want to examine in the room
	Entity* entity = GetParent()->Find(arguments[1], EntityType::ITEM);
	if (!entity)
	{
		entity = Find(arguments[1], EntityType::ITEM);
	}

	if (!entity)
	{
		std::cout << "There is no such thing as a '" << arguments[1] << "'" << std::endl;
		return;
	}
	
	//If there is something like that check it if it's an item,creature etc
	switch (entity->GetType())
	{
	case EntityType::ITEM:
		Item* targetItem = (Item*)entity;
		std::cout << std::endl << "Name: " << targetItem->name<<std::endl;
		std::cout << "Description: " << targetItem->description << std::endl;
		std::cout << "Buff type: " << BuffTypeToString(targetItem->GetBuffType()) << std::endl;


		//Get all the items
		std::vector<const Item*> itemsInStorage;
		for (const auto& child : targetItem->GetChildren()) {
			if (auto childItem = dynamic_cast<const Item*>(child)) {
				itemsInStorage.push_back(childItem);
			}
		}

		//Now lets check if the item has something inside of it
		if (!itemsInStorage.empty()) {
			std::cout << std::endl << "There are following items in the '" << targetItem->name << "'" << std::endl;
			for (const auto& item : itemsInStorage) {
				std::cout << "- " << item->name <<": " << item->description<< std::endl;
			}
		}
		break;
	}
}


void Player::Equip(const std::vector<std::string>& arguments)
{
	//Trying to find the thing we want to equip in our inventory
	Entity* entity = Find(arguments[1], EntityType::ITEM);
	if (!entity)
	{
		entity = Find(arguments[1], EntityType::ITEM);
	}

	if (!entity)
	{
		std::cout << "There is no such thing as a '" << arguments[1] << "' in your bag!" << std::endl;
		return;
	}
	Item* item = (Item*)entity;

	//Now we will check if the item is buff
	if (item)
	{
		if (item->GetItemType() == ItemType::WEAPON)
		{
			// do something with buff item
			weapon = item;
			CalculateStat();
			std::cout << "You equipped '" << item->name << "' weapon." << std::endl;
		}
		else if (item->GetItemType() == ItemType::ARMOR)
		{
			armor = item;
			CalculateStat();
			std::cout << "You equipped '" << item->name << "' armor." << std::endl;
		}
		else if (item->GetItemType() == ItemType::BUFF)
		{
			buffItem = item;
			CalculateStat();
			std::cout << "You now have the '" << BuffTypeToString(buffItem->GetBuffType()) << "' buff." << std::endl;
		}
		else
		{
			std::cout << "This item can not be equipped" << std::endl;
		}
	}
}

void Player::UnEquip(const std::vector<std::string>& arguments)
{
	if (!weapon && !armor && !buffItem)
	{
		std::cout << "There is nothing equipped right now!" << std::endl;
		return;
	}
	//Trying to find the thing we want to equip in our slots
	Entity* entity = Find(arguments[1], EntityType::ITEM);
	if (!entity)
	{
		entity = Find(arguments[1], EntityType::ITEM);
	}

	if (!entity)
	{
		std::cout << "There is no equipped thing as '" << arguments[1] << "' on you!" << std::endl;
		return;
	}
	Item* item = (Item*)entity;

	//Now we will check if the item is weapon,armor or buff
	if (item == weapon)
	{
		weapon = nullptr;
		CalculateStat();
		std::cout << "You unequipped '" << item->name << "' weapon." << std::endl;
	}
	else if (item == armor)
	{
		armor = nullptr;
		CalculateStat();
		std::cout << "You unequipped '" << item->name << "' armor." << std::endl;
	}
	else if (item == buffItem)
	{
		buffItem = nullptr;
		CalculateStat();
		std::cout << "You unequipped '" << item->name << "' buff." << std::endl;
	}
}

void Player::Inventory()
{
	std::vector<const Item*> itemsInBag;
	for (const auto& child : GetChildren()) {
		if (auto childItem = dynamic_cast<const Item*>(child)) {
			itemsInBag.push_back(childItem);
		}
	}

	//Print the items that we have if there are any
	if (!itemsInBag.empty()) {
		std::cout << "\nThere are following items in the inventory:" << std::endl;
		for (const auto& item : itemsInBag) {
			std::cout << "- " << item->name << std::endl;
		}
	}
	else
	{
		std::cout << "There is nothing in your inventory." << std::endl;
	}

}

