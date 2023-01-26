#pragma once
#include "Entity.h"
#include "Room.h"
#include <vector>
#include "Item.h"
#include "BuffType.h"
#include "Stats.h"
class Creature : public Entity
{
public:
	Creature(const char* name, const char* description, Room* room, Stats* stats);
	Room* GetRoom() const;
	virtual const EntityType GetType() const override;
	void GetInfo() const;
	virtual void Attack(const std::vector<std::string>& arguments);
	void MakeAttack();
	void ProcessDamage(int damage);
	void DropAllItems();
	void CalculateStat();
	const int GetDamageCount(const Creature* targetEnemy) const;
	bool IsAlive() const;
	bool Die();
protected:
	Item* buffItem;
	Item* weapon;
	Item* armor;
	Stats* stats;
	int currentHealth;
	Creature* combatTarget;
	bool isPlayerTurn;

};
