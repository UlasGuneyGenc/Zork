#include "Creature.h"

Zork::Creature::Creature(const char* name, const char* description, Room* room) : Entity(name, description, (Entity*)room)
{
}
