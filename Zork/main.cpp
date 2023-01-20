#include <iostream>
#include "World.h"

int main()
{

    //Initiliaze world
    World world;
	std::string player_input;

	//loop to enter string
	while (1)
	{
		getline(std::cin, player_input);

		if (player_input == "exit" || player_input == "quit" || player_input == "q")
			break;
		else
			//TO DO
			std::cout << "I did not understand you!\n";
			continue;

	}

	std::cout << "\nThank you for playing, Bye!\n";
	return 0;
}