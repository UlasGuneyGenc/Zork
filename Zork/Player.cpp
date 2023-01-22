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
	Item* item = (Item*)(GetParent()->Find(arguments[1], EntityType::ITEM));

	if (item == nullptr)
	{
		std::cout << "There is no item named '"<< arguments[1] << "' in the current room." << std::endl;
		return;
	}

	item->ChangeParent(this);

	std::cout << std::endl << "You took the '" << item->name <<"'." << std::endl;
}
