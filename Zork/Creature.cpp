#include "Creature.h"
#include <iostream>
#include <map>
#include "Npc.h"
#include <thread>

Creature::Creature(const char* name, const char* description, Room* room, Stats* stats) : Entity(name, description, (Entity*)room)
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

    // Search for enemy in the room
    for (const auto& child : GetRoom()->GetChildren()) {
        if (auto ex = dynamic_cast<const Npc*>(child)) {
            enemy = (Npc*)ex;
        }
    }
    if (enemy == nullptr) {
        std::cout << "There is nothing to attack!" << std::endl;
        return;
    }
    combatTarget = enemy;
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
            return;
        }
        enemy->MakeAttack();
        std::cout << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(1));
        if (!this->IsAlive()) {
            std::cout << "You lost the battle" << std::endl;
            DropAllItems();
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
    //Get all the items that creature has
    std::vector<Item*> itemsInBag;
    for (const auto& child : GetChildren()) {
        if (auto childItem = dynamic_cast<Item*>(child)) {
            itemsInBag.push_back(childItem);
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

const int Creature::GetDamageCount(const Creature* targetEnemy) const
{
    int random_number = rand() % 21 - 10; // generates a random number between -10 and 10
    return stats->getAttack() - (stats->getAttack() * targetEnemy->stats->getDefence() / 100) + random_number;
}

bool Creature::IsAlive() const
{
    return currentHealth>0;
}

