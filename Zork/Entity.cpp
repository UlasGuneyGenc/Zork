#include "Entity.h"
#include <iostream>
#include "Helpers.h"

Entity::Entity(const char* name, const char* description, Entity* parent) : name(name), description(description), parent(parent)
{
	this->name = name;
	this->description = description;
	if (parent != nullptr) {
		parent->AddChild(this);
	}
}

void Entity::Look() const
{
	std::cout << name << std::endl << description << std::endl;
}

void Entity::Update()
{
}

const EntityType Entity::GetType() const
{
	return EntityType::ENTITY;
}

Entity* Entity::GetParent() const
{
	return parent;
}

const void Entity::ChangeParent(Entity* newParent)
{
	if (parent) {
		parent->RemoveChild(this);
	}
	parent = newParent;
	if (parent) {
		parent->AddChild(this);
	}
}

const std::list<Entity*>& Entity::GetChildren() const
{
	return children;
}

void Entity::AddChild(Entity* child)
{
	children.push_back(child);
}

void Entity::RemoveChild(Entity* child)
{
	children.remove(child);
}

Entity* Entity::Find(const std::string& name, EntityType type) const
{
	for (const auto& child : children) {
		if (toLowerCase(child->name) == toLowerCase(name)) {
			return child;
		}
	}
	return nullptr;
}

Entity* Entity::Find(const std::string& name) const
{
	for (const auto& child : children) {
		if (toLowerCase(child->name) == toLowerCase(name)) {
			return child;
		}
	}
	return nullptr;
}
