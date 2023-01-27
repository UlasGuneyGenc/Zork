#include <iostream>
#include <map>
#include <thread>
#include "Room.h"
#include "Creature.h"
#include "Npc.h"
#include "Helpers.h"

Creature::Creature(const char* name, const char* description, Room* room, Stats* stats) : Entity(name, description, (Entity*)room)
{
	this->stats = stats;
	currentHealth = stats->getHealth();
}

Room* Creature::GetRoom() const
{
	if (GetParent()->GetType() == EntityType::ROOM)
	{
		return static_cast<Room*>(GetParent());
	}
	return nullptr;
}

const EntityType Creature::GetType() const
{
	return EntityType::CREATURE;
}


void Creature::GetInfo() const
{
	std::cout << std::endl << name<<"'s stats" << std::endl;
	std::cout << "  Health:  " << currentHealth << "/" << stats->getHealth() << std::endl;
	std::cout << "  Attack:  " << stats->getAttack() << std::endl;
	std::cout << "  Defence: " << stats->getDefence() << std::endl;
    if (buffItem) {
        std::cout << "  Buff Type:  " << BuffTypeToString(buffItem->GetBuffType()) << std::endl;
    }
}

void Creature::Attack(const std::vector<std::string>& arguments)
{
    Npc* enemy = nullptr;
    const std::list<Entity*>& roomChildren = GetRoom()->GetChildren();
    // Search for enemy in the room
    for (const auto& child : roomChildren) {
        if (child->GetType() == EntityType::NPC && toLowerCase(child->name) == arguments[1])
        {
            enemy = (Npc*)child;
        }
    }
    if (enemy == nullptr) {
        std::cout << "There is no emeny called '" << arguments[1] << "' in this room!" << std::endl;
        return;
    }
    combatTarget = enemy;
    const bool isLastBoss = enemy->GetIsLastBoss();

    enemy->combatTarget = this;
    while (this->IsAlive() && enemy->IsAlive()) {
        if (!enemy->IsAlive()) {
            std::cout << "You won the battle" << std::endl;
            combatTarget->DropAllItems();
            return;
        }
        MakeAttack();
        if (!enemy->IsAlive()) {
            std::cout << "You won the battle" << std::endl;
            combatTarget->DropAllItems();
            if (isLastBoss)
            {
                std::cout << "Congratulations! You beat the game!" << std::endl;
                Die();
            }
            return;
        }
        enemy->MakeAttack();
        std::cout << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(1));
        if (!this->IsAlive()) {
            std::cout << "You lost the battle" << std::endl;
            return;
        }
    }
    std::cout << "'" << enemy->name << "' is already dead!" << std::endl;
}

void Creature::MakeAttack()
{
    if (combatTarget == nullptr)
    {
        return;
    }

    if (!combatTarget->IsAlive())
    {
        std::cout << combatTarget->name << " is dead." << std::endl;
        combatTarget = nullptr;
        return;
    }

    if (this->combatTarget == nullptr) {
        std::cout << "There is nothing to attack!" << std::endl;
        return;
    }
    int damage = GetDamageCount(combatTarget);
    combatTarget->ProcessDamage(damage);
    std::cout << "'" << name << "' hit " << damage << " to '" << combatTarget->name << "' HP: " << combatTarget->currentHealth << "/" << combatTarget->stats->getHealth() << std::endl;
    if (combatTarget->stats->getHealth() <= 0) {
        std::cout << combatTarget->name << " is dead." << std::endl;
    }
}

void Creature::ProcessDamage(int damage) 
{
    currentHealth -= damage;
}

void Creature::DropAllItems()
{
    const std::list<Entity*>& children = GetChildren();

    //Get all the items that creature has
    std::vector<Item*> itemsInBag;
    for (const auto& child : children) {
        if (child->GetType() == EntityType::ITEM)
        {
            itemsInBag.push_back(static_cast<Item*>(child));
        }
    }
    if (!itemsInBag.empty()) {
        std::cout <<"'"<<name<<"' dropped following items:" << std::endl;
        for (const auto& item : itemsInBag) {
            item->ChangeParent((Entity*)GetRoom());
            std::cout << "- " << item->name << std::endl;
        }
    }
}

void Creature::CalculateStat()
{
    const int previous_damage = stats->getHealth() - currentHealth;

    // Initialize the stats with default values
    stats->setAllNew(80, 40, 40);

    // Lookup table for stat modifications based on buffType
    const std::map<BuffType, Stats> buffTypeModifiers = {
        {BuffType::AIR, {20, -10, -10}},
        {BuffType::EARTH, {-10, -10, 20}},
        {BuffType::FIRE, {-10, 20, -10}},
        {BuffType::WATER, {-5, 10, -5}},

    };

    // Apply stat modifications based on buffType
    if (buffItem)
    {
        const Stats modifications = buffTypeModifiers.at(buffItem->GetBuffType());
        stats->incrementAll(modifications.getHealth(), modifications.getAttack(), modifications.getDefence());
    }
    // Apply stat modifications based on equipped items
    if (weapon) {
        const auto weapon_stats = weapon->GetStats();
        stats->incrementAll(weapon_stats.getHealth(), weapon_stats.getAttack(), weapon_stats.getDefence());
    }
    if (armor) {
        const auto armor_stats = armor->GetStats();
        stats->incrementAll(armor_stats.getHealth(), armor_stats.getAttack(), armor_stats.getDefence());
    }

    // Ensure currentHealth is not greater than max health and if there is a damage keep it
    int new_max_health = stats->getHealth();
    currentHealth = previous_damage == 0 ? new_max_health : new_max_health - previous_damage;

}

const int Creature::GetDamageCount(const Creature* targetEnemy) const
{
    int random_number = rand() % 21 - 10; // generates a random number between -10 and 10
    return stats->getAttack() - (stats->getAttack() * targetEnemy->stats->getDefence() / 100) + random_number;
}

bool Creature::IsAlive() const
{
    return currentHealth>0;
}

bool Creature::Die()
{
    currentHealth = 0;
    return false;
}

