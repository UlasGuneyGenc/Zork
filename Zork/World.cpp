#include <iostream>
#include "World.h"
#include "Room.h"
#include "Player.h"
#include "Exit.h"
#include <list>
#include "Item.h"

World::World()
{
	//Game beginning and getting character name
	std::cout << "You slowly open your eyes and find yourself lying on a cold, stone floor." << std::endl;
	std::cout << "You appear to be in an abandoned church, with boarded-up windows and overturned pews." << std::endl;
	std::cout << "You can't remember how you got here or why you're here. But you realize that you have to find your way out." << std::endl;
	std::cout << "------------------------------------------------------" << std::endl;


	// Create rooms
	Room* abandonedChurch = new Room("Abandoned Church", "Abandoned Church is a decaying, boarded-up structure. Pews overturned and altar is covered in dust and cobwebs. Scent of decay and neglect lingers in the air.");
	Room* garden = new Room("Garden", "The Garden is overgrown and unkempt, with wilted flowers and tall weeds. Neglected, with a sense of ethereal beauty.");
	Room* graveyard = new Room("Graveyard", "Graveyard is overgrown, with broken and knocked over gravestones. Air thick with sense of death and decay, eerie silence hangs over the area.");


	// Create player
	Player* player = new Player("Hero", "Mighty hero!", abandonedChurch);
	this->player = player;

	// Create exits
	Exit* exitChurchToGarden = new Exit("Broken door", "The exit from the church leads to a small, overgrown garden.", Direction::NORTH, abandonedChurch, garden);
	Exit* exitGardenToChurch = new Exit("Broken door", "The exit from the garden leads back to the abandoned church.", Direction::SOUTH, garden, abandonedChurch);
	Exit* exitGardenToGraveyard = new Exit("Muddy broken wall", "The exit from the garden leads to a neglected graveyard.", Direction::WEST, garden, graveyard);
	Exit* exitGraveyardToGarden = new Exit("Muddy broken wall", "The exit from the graveyard leads to a small, overgrown garden.", Direction::EAST, graveyard, garden);

	//Create storage items
	Item* smallChest = new Item("Chest", "Small wooden chest is worn and weathered, crafted from rough-hewn planks of wood. Iron hinges and lock rusted with age, giving off a sense of mystery.", abandonedChurch, ItemType::STORAGE);


	//Create items in the storages
	Item* rustyKey = new Item("Key", "Rusty Iron key, small and worn, covered in rust, teeth still sharp.",smallChest,ItemType::KEY);


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

void World::HandleInput(const std::vector<std::string>& arguments)
{
	switch (arguments.size()) {
	case 0:
		std::cout << "You did not type anything!" << std::endl;
		break;
	case 1:
		if (arguments[0] == "exit" || arguments[0] == "quit" || arguments[0] == "q") {
			gameOver = true;
		}
		else if (arguments[0] == "look" || arguments[0] == "info") {
			player->Look();
		}
		else if (arguments[0] == "bag" || arguments[0] == "inventory" || arguments[0] == "b" || arguments[0] == "i") {
			player->Inventory();
		}
		else
			std::cout << "I did not understand you!" << std::endl;
		break;
	case 2:
		if (arguments[0] == "move" || arguments[0] == "go") {
			player->Move(arguments);
		}
		else if (arguments[0] == "take" || arguments[0] == "get")
		{
			player->Take(arguments);
		}
		else if (arguments[0] == "drop" )
		{
			player->Drop(arguments);
		}
		else if (arguments[0] == "examine" || arguments[0] == "info")
		{
			player->Examine(arguments);
		}
		//TO DO
		break;
	case 3:
		//TO DO
		break;
	case 4:
		if ((arguments[0] == "take" || arguments[0] == "get") && arguments[2] == "from")
		{
			player->Take(arguments);
		}
		break;
	default:
		std::cout << "I did not understand you!" << std::endl;
		break;
	}
}

bool World::IsGameOver() const
{
	return gameOver;
}

