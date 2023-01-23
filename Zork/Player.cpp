#include "Player.h"
#include "Exit.h"
#include "Direction.h"
#include <iostream>
#include "Item.h"

Player::Player(const char* name, const char* description, Room* room) : Creature(name, description, room)
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

	//Try to find the thing we want to examine
	Entity* entity = (Item*)(GetParent()->Find(arguments[1], EntityType::ITEM));

	if (entity == nullptr)
	{
		std::cout << "There is no such thing as a '" << arguments[1] << "'" << std::endl;
		return;
	}
	
	//If there is something like that check it if it's an item,creature etc
	switch (entity->GetType())
	{
	case EntityType::ITEM:
		std::cout << std::endl << "Name: " << entity->name<<std::endl;
		std::cout << "Description: " << entity->description << std::endl;


		//Get all the items
		std::vector<const Item*> itemsInStorage;
		for (const auto& child : entity->GetChildren()) {
			if (auto childItem = dynamic_cast<const Item*>(child)) {
				itemsInStorage.push_back(childItem);
			}
		}

		//Now lets check if the item has something inside of it
		if (!itemsInStorage.empty()) {
			std::cout << std::endl << "There are following items in the '" << entity->name << "'" << std::endl;
			for (const auto& item : itemsInStorage) {
				std::cout << "- " << item->name << std::endl;
			}
		}
		break;
	}
}
