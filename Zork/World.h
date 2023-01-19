#pragma once
#include <vector>
#include <list>

class Entity;
class Player;
class Room;

namespace Zork
{
	class World
	{
	public:
		World();
	private:
		std::vector<Entity*> entities;
		Player* player;
	};
}