#include "Creature.h"
#include <iostream>
#include <map>

Creature::Creature(const char* name, const char* description, Room* room, BuffType buffType, Stats* stats) : Entity(name, description, (Entity*)room)
{
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
    if (buffItem) {
        std::cout << "  Buff Type:  " << BuffTypeToString(buffItem->GetBuffType()) << std::endl;
    }
}

void Creature::CalculateStat()
{
    int previous_damage = stats->getHealth() - currentHealth;

    // Initialize the stats with default values
    stats->setAllNew(40, 40, 40);

    // Lookup table for stat modifications based on buffType
    const std::map<BuffType, Stats> buffTypeModifiers = {
        {BuffType::AIR, {10, -5, -5}},
        {BuffType::EARTH, {-10, -10, 20}},
        {BuffType::FIRE, {-10, 20, -10}},
        {BuffType::WATER, {-5, 10, -5}},

    };

    // Apply stat modifications based on buffType
    if (buffItem)
    {
        const Stats modifications = buffTypeModifiers.at(buffItem->GetBuffType());
        stats->modifyAll(modifications.getHealth(), modifications.getAttack(), modifications.getDefence());
    }
    // Apply stat modifications based on equipped items
    if (weapon) {
        const auto weapon_stats = weapon->GetStats();
        stats->modifyAll(weapon_stats.getHealth(), weapon_stats.getAttack(), weapon_stats.getDefence());
    }
    if (armor) {
        const auto armor_stats = armor->GetStats();
        stats->modifyAll(armor_stats.getHealth(), armor_stats.getAttack(), armor_stats.getDefence());
    }

    // Ensure currentHealth is not greater than max health and if there is a damage keep it
    int new_max_health = stats->getHealth();
    currentHealth = previous_damage == 0 ? new_max_health : new_max_health - previous_damage;

}

