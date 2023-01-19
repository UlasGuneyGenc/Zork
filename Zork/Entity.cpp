#include "Entity.h"

Entity::Entity(const char* name, const char* description, Entity* parent) : name(name), description(description), parent(parent)
{
}

void Entity::Insert(Entity* entity) {
	entities.push_back(entity);
}

void Entity::Remove(Entity* entity) {
	entities.remove(entity);
}