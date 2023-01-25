#pragma once
#include "Entity.h"
#include "Room.h"
#include "Item.h"
#include "BuffType.h"
#include "Stats.h"
#include <vector>
class Creature : public Entity
{
public:
	Creature(const char* name, const char* description, Room* room, Stats* stats);
	Room* GetRoom() const;
	virtual void Update();
	virtual const EntityType GetType() const;
	virtual void GetInfo() const;
	virtual void Attack(const std::vector<std::string>& arguments);
	virtual void MakeAttack();
	virtual void ProcessDamage(int damage);
	virtual void DropAllItems();
	void CalculateStat();
	const int GetDamageCount(const Creature* targetEnemy) const;
	bool IsAlive() const;

protected:
	Item* buffItem;
	Item* weapon;
	Item* armor;
	Stats* stats;
	int currentHealth;
	Creature* combatTarget;
	bool isPlayerTurn;

};
