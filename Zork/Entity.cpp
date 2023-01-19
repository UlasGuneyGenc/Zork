#include "Entity.h"

Zork::Entity::Entity(const char* name, const char* description, Entity* parent) : name(name), description(description), parent(parent)
{
}
