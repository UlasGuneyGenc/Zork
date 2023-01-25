#include <iostream>
#include "World.h"
#include "Room.h"
#include "Player.h"
#include "Exit.h"
#include <list>
#include "Item.h"
#include "Stats.h"

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
	Room* theLostCity = new Room("The Lost City", "An ancient, crumbling metropolis long abandoned by its inhabitants and overrun by wild beasts and dangerous magic.");
	Room* theIronKeep = new Room("The Iron Keep", "A massive, impregnable fortress built to defend against invaders, its walls and gates made of solid iron.");
	Room* crystalCaves = new Room("Crystal Caves", "A network of glittering, underground caves said to hold great treasures and powerful magic.");
	Room* cursedSwamp = new Room("Cursed Swamp", "A murky, mist-shrouded bog rumored to be cursed by dark magic and home to deadly monsters.");
	Room* dragonLair = new Room("Dragon's Lair", "A towering, ominous mountain range rumored to be home to fearsome dragons and other deadly creatures.");


	// Create player
	Player* player = new Player("Hero", "Mighty hero!", abandonedChurch, new Stats(40,40,40));
	this->player = player;

	
	//Create storage items
	Item* smallChest = new Item("Chest", "Small wooden chest is worn and weathered, crafted from rough-hewn planks of wood. Iron hinges and lock rusted with age, giving off a sense of mystery.", abandonedChurch, ItemType::STORAGE, BuffType::NONE, Stats());
	Item* bag = new Item("Bag", "Bag.", garden, ItemType::STORAGE, BuffType::NONE, Stats());

	//Create enemies in rooms
	Npc* zga = new Npc("Zga", "You see a giant creature who repeatedly whispers, 'Zga, Zga, Zga'. It seems to be an ancient language. Be careful!", abandonedChurch, BuffType::NONE, new Stats(60, 20, 60));

	//Create items 
	Item* rustyKey = new Item("Key", "Rusty Iron key, small and worn, covered in rust, teeth still sharp.", zga, ItemType::KEY, BuffType::NONE, Stats());
	Item* fireBuff = new Item("FireScroll", "A magical scroll that warms your heart even at the sight of it.", smallChest, ItemType::BUFF, BuffType::FIRE, Stats());
	Item* sword = new Item("Sword", "Tiny rusty metal sword.", smallChest, ItemType::WEAPON, BuffType::NONE, Stats(5,20,5));
	Item* potionOne = new Item("Potion", "Heals the drinker and replenishes any lost health", zga, ItemType::POTION, BuffType::NONE, Stats(50, 0, 0));

	// Create exits
	Exit* exitChurchToGarden = new Exit("Broken door", "The exit from the church leads to a small, overgrown garden.", Direction::NORTH, abandonedChurch, garden, true, rustyKey);
	Exit* exitGardenToChurch = new Exit("Broken door", "The exit from the garden leads back to the abandoned church.", Direction::SOUTH, garden, abandonedChurch, false, nullptr);
	Exit* exitGardenToGraveyard = new Exit("Muddy broken wall", "The exit from the garden leads to a neglected graveyard.", Direction::WEST, garden, graveyard, false, nullptr);
	Exit* exitGraveyardToGarden = new Exit("Muddy broken wall", "The exit from the graveyard leads to a small, overgrown garden.", Direction::EAST, graveyard, garden, false, nullptr);
	Exit* exitGardenToIronKeep = new Exit("Iron gate", "A secret gate hidden by thorny bushes leads to the Iron Keep.", Direction::EAST, garden, theIronKeep, true, nullptr);
	Exit* exitIronKeepToGarden = new Exit("Iron gate", "A secret gate hidden by thorny bushes leads to the garden.", Direction::WEST, theIronKeep, garden, false, nullptr);
	Exit* exitGardenToLostCity = new Exit("Magical Entrance", "A hidden path that leads from garden to the ruins of the Lost City.", Direction::NORTH, garden, theLostCity, false, nullptr);
	Exit* exitLostCityToGarden = new Exit("Magical Entrance", "A hidden path that leads from ruins of the Lost City to the garden.", Direction::SOUTH, theLostCity, garden, false, nullptr);
	Exit* exitLostCityToCrystalCave = new Exit("Crystal Entrance", "A narrow and winding path that leads from the Lost City ruins to the Crystal Caves.", Direction::WEST, theLostCity, crystalCaves, true, nullptr);
	Exit* exitCrystalCaveToLostCity= new Exit("Crystal Entrance", "A narrow and winding path that leads from Crystal Caves to the Lost City.", Direction::EAST, crystalCaves, theLostCity, false, nullptr);
	Exit* exitCrystalCaveToCursedSwamp= new Exit("Cursed Exit", "A damp and dark path that leads from the Crystal Caves to the Cursed Swamp.", Direction::NORTH, crystalCaves, cursedSwamp, false, nullptr);
	Exit* exitCursedSwampToCrystalCave = new Exit("Cursed Exit", "A damp and dark path that leads from the Cursed Swamp to the Crystal Caves.", Direction::SOUTH, cursedSwamp, crystalCaves, false, nullptr);
	Exit* exitCursedSwampToDragonLair = new Exit("Dragon Path", "A narrow and winding path that leads from the Cursed Swamp to the Dragon's Lair.", Direction::EAST, cursedSwamp, dragonLair, true, nullptr);
	Exit* exitDragonLairToCursedSwamp = new Exit("Cursed Exit", "A narrow and winding path that leads from the Dragon's Lair to the Cursed Swamp.", Direction::WEST, dragonLair, cursedSwamp, false, nullptr);


	//rooms
	entities.push_back(abandonedChurch);
	entities.push_back(garden);
	entities.push_back(graveyard);
	entities.push_back(theLostCity);
	entities.push_back(theIronKeep);
	entities.push_back(crystalCaves);
	entities.push_back(cursedSwamp);
	entities.push_back(dragonLair);
	//player
	entities.push_back(player);
	//storage items
	entities.push_back(smallChest);
	entities.push_back(bag);
	//monsters
	entities.push_back(zga);
	//items
	entities.push_back(rustyKey);
	entities.push_back(fireBuff);
	entities.push_back(sword);
	entities.push_back(potionOne);
	//exits
	entities.push_back(exitChurchToGarden);
	entities.push_back(exitGardenToChurch);
	entities.push_back(exitGardenToGraveyard);
	entities.push_back(exitGraveyardToGarden);
	entities.push_back(exitGardenToIronKeep);
	entities.push_back(exitIronKeepToGarden);
	entities.push_back(exitGardenToLostCity);
	entities.push_back(exitLostCityToGarden);
	entities.push_back(exitLostCityToCrystalCave);
	entities.push_back(exitCrystalCaveToLostCity);
	entities.push_back(exitCrystalCaveToCursedSwamp);
	entities.push_back(exitCursedSwampToCrystalCave);
	entities.push_back(exitCursedSwampToDragonLair);
	entities.push_back(exitDragonLairToCursedSwamp);
	player->GetParent()->Look();

}

World::~World()
{
	for (Entity* entity : entities)
	{
		delete entity;
	}
}

void World::HandleInput(const std::vector<std::string>& arguments)
{
	switch (arguments.size()) {
	case 0:
		std::cout << "You did not type anything!" << std::endl;
		break;
	case 1:
		if (arguments[0] == "exit" || arguments[0] == "quit" || arguments[0] == "q") {
			player->Die();
		}
		else if (arguments[0] == "look" || arguments[0] == "info") {
			player->Look();
		}
		else if (arguments[0] == "bag" || arguments[0] == "inventory" || arguments[0] == "b" || arguments[0] == "i") {
			player->ShowInventory();
		}
		else if (arguments[0] == "stats" || arguments[0] == "stat") {
			player->GetInfo();
		}
		else 
		{
			std::cout << "I did not understand you!" << std::endl;
		}
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
		else if (arguments[0] == "examine" || arguments[0] == "info" || arguments[0] == "look")
		{
			player->Examine(arguments);
		}
		else if (arguments[0] == "detail" )
		{
			player->Detail(arguments);
		}
		else if (arguments[0] == "equip" || arguments[0] == "eq")
		{
			player->Equip(arguments);
		}
		else if (arguments[0] == "unequip")
		{
			player->UnEquip(arguments);
		}
		else if (arguments[0] == "attack")
		{
			player->Attack(arguments);
		}
		else if (arguments[0] == "unlock")
		{
			player->Unlock(arguments);
		}
		else if (arguments[0] == "use")
		{
			player->Use(arguments);
		}
		//TO DO
		break;
	case 4:
		if ((arguments[0] == "take" || arguments[0] == "get") && arguments[2] == "from")
		{
			player->Take(arguments);
		}
		else
		{
			std::cout << "I did not understand you!" << std::endl;
		}
		break;
	default:
		std::cout << "I did not understand you!" << std::endl;
		break;
	}
}

bool World::IsGameOver() const
{
	return !(player->IsAlive());
}

