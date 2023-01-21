#pragma once
#include <iostream>
#include <list>
#include "Entity.h"
#include "Player.h"
#include <vector>


class World
{
public:
	World();
	~World();
	void HandleInput(const std::vector<std::string>& words);
	bool IsGameOver() const;

private:
	Player* player;
	std::list<Entity*> entities;
	bool gameOver = false;
};
