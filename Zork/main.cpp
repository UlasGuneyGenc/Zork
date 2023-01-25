#include <iostream>
#include "World.h"
#include <vector>
#include "Helpers.h"

int main()
{
    //Initiliaze world
    World world;
	std::string playerInput;

	//loop to enter string
	while (!world.IsGameOver())
	{
		getline(std::cin, playerInput);

		std::vector<std::string> verbs = GetVerbs(toLowerCase(playerInput));
		world.HandleInput(verbs);
	}

	std::cout << "\nThank you for playing, Bye!\n";
	return 0;
}