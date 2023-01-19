#pragma once
#include <iostream>
#include <list>
#include "Entity.h"
#include "Player.h"


class World
{
public:
	World();
	~World();

private:
	Player* player;
	std::list<Entity*> entities;
};
