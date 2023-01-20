#include <iostream>
#include "World.h"
#include "Room.h"
#include "Player.h"
#include "Exit.h"
#include <list>

World::World()
{
	//Game beginning and getting character name
	std::cout << "You slowly open your eyes and find yourself lying on a cold, stone floor." << std::endl;
	std::cout << "You appear to be in an abandoned church, with boarded-up windows and overturned pews." << std::endl;
	std::cout << "You can't remember how you got here or why you're here. But you realize that you have to find your way out." << std::endl;
	

	// Create rooms
	Room* abandonedChurch = new Room("Abandoned Church", "Abandoned Church is a decaying, boarded-up structure. Pews overturned and altar is covered in dust and cobwebs. Scent of decay and neglect lingers in the air.");
	Room* garden = new Room("Garden", "The Garden is overgrown and unkempt, with wilted flowers and tall weeds. Neglected, with a sense of ethereal beauty.");
	Room* graveyard = new Room("Graveyard", "Graveyard is overgrown, with broken and knocked over gravestones. Air thick with sense of death and decay, eerie silence hangs over the area.");


	// Create player
	Player* player = new Player("Hero", "Mighty hero!", abandonedChurch);

	// Create exits
	Exit* exitChurchToGarden = new Exit("Broken door", "The exit from the church leads to a small, overgrown garden.", Direction::NORTH, abandonedChurch, garden);
	Exit* exitGardenToChurch = new Exit("Broken door", "The exit from the garden leads back to the abandoned church.", Direction::SOUTH, garden, abandonedChurch);
	Exit* exitGardenToGraveyard = new Exit("Muddy broken wall", "The exit from the garden leads to a neglected graveyard.", Direction::WEST, garden, graveyard);
	Exit* exitGraveyardToGarden = new Exit("Muddy broken wall", "The exit from the graveyard leads to a small, overgrown garden.", Direction::EAST, graveyard, garden);
	
	entities.push_back(abandonedChurch);
	entities.push_back(garden);
	entities.push_back(graveyard);
	entities.push_back(player);
	entities.push_back(exitChurchToGarden);
	entities.push_back(exitGardenToChurch);
	entities.push_back(exitGardenToGraveyard);
	entities.push_back(exitGraveyardToGarden);

	player->GetParent()->Look();

}

World::~World()
{
	while (!entities.empty())
		delete entities.front(), entities.pop_front();
	entities.clear();
}

