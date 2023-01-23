#include "Creature.h"
#include <iostream>

Creature::Creature(const char* name, const char* description, Room* room, BuffType buffType, Stats* stats) : Entity(name, description, (Entity*)room)
{
	this->buffType = buffType;
	this->stats = stats;
	currentHealth = stats->getHealth();
}

const Room* Creature::GetRoom() const
{
	if (GetParent()->GetType() == EntityType::ROOM)
	{
		return (Room*)GetParent();
	}
	return nullptr;
}

void Creature::Update()
{

}

const EntityType Creature::GetType() const
{
	return EntityType::CREATURE;
}


void Creature::GetInfo() const
{
	std::cout << std::endl << "Your stats" << std::endl;
	std::cout << "  Health:  " << currentHealth << "/" << stats->getHealth() << std::endl;
	std::cout << "  Attack:  " << stats->getAttack() << std::endl;
	std::cout << "  Defence: " << stats->getDefence() << std::endl;
	std::cout << "  Buff Type:  " << BuffTypeToString(buffType) << std::endl;

}

void Creature::CalculateBuffEffect()
{
	switch (buffType)
	{
	case BuffType::AIR:
		stats->modifyAll(10,-5,-5);
		break;
	case BuffType::EARTH:
		stats->modifyAll(-10, -10, 20);
		break;
	case BuffType::FIRE:
		stats->modifyAll(-10, 20, -10);
		break;
	case BuffType::WATER:
		stats->modifyAll(-5, 10, -5);
		break;
	default:
		break;
	}

	if (currentHealth>stats->getHealth())
	{
		currentHealth = stats->getHealth();
	}
}
