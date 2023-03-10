#pragma once
#include <iostream>
#include <list>
#include <vector>
#include "Entity.h"
#include "Player.h"


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
};
