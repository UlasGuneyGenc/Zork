#include "Player.h"
#include "Exit.h"
#include "Direction.h"
#include <iostream>

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
