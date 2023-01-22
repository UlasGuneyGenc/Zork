#include <iostream>
#include "World.h"
#include <vector>
#include "Helpers.h"

int main()
{
    //Initiliaze world
    World world;
	std::string player_input;

	//loop to enter string
	while (!world.IsGameOver())
	{
		getline(std::cin, player_input);

		std::vector<std::string> verbs = GetVerbs(toLowerCase(player_input));
		world.HandleInput(verbs);
	}

	std::cout << "\nThank you for playing, Bye!\n";
	return 0;
}