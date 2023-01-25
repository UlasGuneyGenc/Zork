#pragma once
#include "Creature.h"
#include <vector>
#include "Npc.h"

class Player : public Creature
{
public:
	Player(const char* name, const char* description, Room* room, Stats* stats);
	void Look() const override;
	void Move(const std::vector<std::string>& arguments);
	void Take(const std::vector<std::string>& arguments);
	void Drop(const std::vector<std::string>& arguments);
	void Examine(const std::vector<std::string>& arguments);
	void Equip(const std::vector<std::string>& arguments);
	void UnEquip(const std::vector<std::string>& arguments);
	void Attack(const std::vector<std::string>& arguments);
	void Unlock(const std::vector<std::string>& arguments);
	void Detail(const std::vector<std::string>& arguments);
	void Use(const std::vector<std::string>& arguments);
	void ShowInventory();
	bool Die();

};
