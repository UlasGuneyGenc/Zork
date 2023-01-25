#pragma once
#include <string>
#include <list>
#include "EntityType.h"

class Entity
{		
public:
	Entity(const char* name, const char* description, Entity* parent);

	virtual void Look() const;
	virtual const EntityType GetType() const;
	virtual Entity* GetParent() const;
	const void ChangeParent(Entity* newParent);
	const std::list<Entity*>& GetChildren() const;
	void AddChild(Entity* child);
	void RemoveChild(Entity* child);
	Entity* Find(const std::string& name, EntityType type) const;
	Entity* Find(const std::string& childName) const;

	std::string name;
	std::string description;
private:
	Entity* parent;
	std::list<Entity*> children;
};
