#include <iostream>
#include "Player.h"
#include "Exit.h"
#include "Direction.h"
#include "Item.h"
#include "Stats.h"
#include "Room.h"


Player::Player(const char* name, const char* description, Room* room, Stats* stats) : Creature(name, description, room, stats)
{
}

void Player::Look() const
{
	GetParent()->Look();
}

void Player::Move(const std::vector<std::string>& arguments)
{
	Exit* wantedExit = GetRoom()->GetExit(StringToDirection(arguments[1]));
	if (!wantedExit) {
		return;
	}

	if (wantedExit->IsLocked()) {
		std::cout << "Exit is locked." << std::endl;
	}
	else {
		ChangeParent(wantedExit->GetDestinationRoom());
		GetParent()->Look();
	}
}

void Player::Take(const std::vector<std::string>& arguments)
{
	switch (arguments.size()) {
	case 2:
	{
		Item* item = static_cast<Item*>(GetParent()->Find(arguments[1], EntityType::ITEM));
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
		Entity* entity = static_cast<Item*>(GetParent()->Find(arguments[3], EntityType::ITEM));
		if (entity == nullptr)
		{
			std::cout << "There is no such thing as '" << arguments[1] << "' or '" << arguments[3] << "' " << std::endl;
			return;
		}
		if (entity->GetType() == EntityType::ITEM)
		{
			Item* childItem = static_cast<Item*>(entity->Find(arguments[1]));
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
	Item* item = static_cast<Item*>(Find(arguments[1], EntityType::ITEM));
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
	Entity* entity = GetParent()->Find(arguments[1]);
	if (!entity)
	{
		entity = Find(arguments[1]);
	}

	if (!entity)
	{
		std::cout << "There is no such thing as a '" << arguments[1] << "'" << std::endl;
		return;
	}
	
	//If there is something like that check it if it's an item,creature etc
	if (entity->GetType() == EntityType::ITEM) {
		Item* targetItem = (Item*)entity;
		const std::list<Entity*>& children = targetItem->GetChildren();
		std::cout << std::endl << "Name: " << targetItem->name << std::endl;
		std::cout << "Description: " << targetItem->description << std::endl;
		std::cout << "Buff type: " << BuffTypeToString(targetItem->GetBuffType()) << std::endl;

		//Get all the items
		std::vector<const Item*> itemsInStorage;
		for (const auto& child : children) {
			if (child->GetType() == EntityType::ITEM)
			{
				itemsInStorage.push_back(static_cast<Item*>(child));
			}
		}

		//Now lets check if the item has something inside of it
		if (!itemsInStorage.empty()) {
			std::cout << std::endl << "There are following items in the '" << targetItem->name << "'" << std::endl;
			for (const auto& item : itemsInStorage) {
				std::cout << "- " << item->name << ": " << item->description << std::endl;
			}
		}
	}
	else if (entity->GetType() == EntityType::NPC) {
		const Npc* targetNpc = (Npc*)entity;
		std::cout << std::endl << "Name: " << targetNpc->name << std::endl;
		std::cout << "Description: " << targetNpc->description << std::endl;
		targetNpc->GetInfo();
	}
}


void Player::Equip(const std::vector<std::string>& arguments)
{
	//Trying to find the thing we want to equip in our inventory
	Entity* entity = Find(arguments[1], EntityType::ITEM);

	if (!entity)
	{
		std::cout << "There is no such thing as a '" << arguments[1] << "' in your bag!" << std::endl;
		return;
	}
	Item* item = (Item*)entity;

	//Now we will check if the item is buff,weapon or armor
	if (item)
	{
		if (item->GetItemType() == ItemType::WEAPON)
		{
			// assign weapon item
			weapon = item;
			CalculateStat();
			std::cout << "You equipped '" << item->name << "' weapon." << std::endl;
		}
		else if (item->GetItemType() == ItemType::ARMOR)
		{
			// assign armor item
			armor = item;
			CalculateStat();
			std::cout << "You equipped '" << item->name << "' armor." << std::endl;
		}
		else if (item->GetItemType() == ItemType::BUFF)
		{
			// assign buff item
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
	Entity* entity = Find(arguments[1]);
	

	if (!entity)
	{
		std::cout << "There is no equipped thing '" << arguments[1] << "' on you!" << std::endl;
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

void Player::Attack(const std::vector<std::string>& arguments)
{
	Creature::Attack(arguments);
}

void Player::Unlock(const std::vector<std::string>& arguments)
{
	Exit* wantedExit = GetRoom()->GetExit(StringToDirection(arguments[1]));

	//check if exit exists and it is locked
	if (!wantedExit) {
		return;
	}

	if (!wantedExit->IsLocked())
	{
		std::cout << "Exit is not locked you don't need to unlock it!" << std::endl;
	}
	else {
		const Item* key = wantedExit->GetKey();

		//check if we have the key
		Item* keyOnPlayer = (Item*)Find(key->name);

		if (keyOnPlayer)
		{
			wantedExit->Unlock();
			keyOnPlayer->ChangeParent((Entity*)wantedExit);
			std::cout << DirectionToString(wantedExit->GetDirection()) << " exit is unlocked!" << std::endl;
		}
		else
		{
			std::cout << "This key does not work in here!" << std::endl;
		}
	}
}

void Player::Detail(const std::vector<std::string>& arguments)
{
	const Exit* wantedExit = GetRoom()->GetExit(StringToDirection(arguments[1]));
	if (wantedExit)
	{
		wantedExit->Look();
	}
}

void Player::Use(const std::vector<std::string>& arguments)
{
	Entity* entity = Find(arguments[1], EntityType::ITEM);

	if (!entity)
	{
		std::cout << "There is no such thing as '" << arguments[1] << "' to use!" << std::endl;
		return;
	}
	Item* item = (Item*)entity;

	if (item->GetItemType() == ItemType::POTION)
	{
		int random_number = rand() % 21 - 10; // generates a random number between -10 and 10
		currentHealth = std::min(currentHealth + random_number + item->GetStats().getHealth(), stats->getHealth());
		std::cout << "You replenished your health. HP: " << currentHealth<< "/"<< stats->getHealth() << std::endl;
		item->ChangeParent(GetRoom());
		RemoveChild(item);
	}
	else
	{
		std::cout << "That is not a thing to use!"<< std::endl;
	}
}

void Player::ShowInventory()
{
	const std::list<Entity*>& children = GetChildren();
	std::vector<Item*> itemsInBag;
	itemsInBag.reserve(children.size());

	for (const auto& child : children) {
		if (child->GetType() == EntityType::ITEM)
		{
			itemsInBag.push_back(static_cast<Item*>(child));
		}
	}

	//Print the items that we have if there are any
	if (!itemsInBag.empty()) {
		std::cout << std::endl << "There are following items in the inventory:" << std::endl;
		for (const auto& item : itemsInBag) {
			std::cout << "- " << item->name << std::endl;
		}
	}
	else
	{
		std::cout << "There is nothing in your inventory." << std::endl;
	}
}
