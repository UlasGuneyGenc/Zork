#pragma once
#include <string>
#include <list>
#include "EntityType.h"

class Entity
{		
public:
	Entity(const char* name, const char* description, Entity* parent);

	virtual void Look() const;
	virtual void Update();
	virtual const EntityType GetType() const;
	virtual const Entity* GetParent() const;
	virtual const void ChangeParent(Entity* newParent);
	const std::list<Entity*>& GetChildren() const;
	virtual void AddChild(Entity* child);
	virtual void RemoveChild(Entity* child);
	Entity* Find(const std::string& name, EntityType type) const;

	std::string name;
	std::string description;
private:
	Entity* parent;
	std::list<Entity*> children;
};
