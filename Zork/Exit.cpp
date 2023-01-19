#include "Exit.h"
#include "Room.h"

Exit::Exit(const char* name, const char* description, Direction direction, Room* origin, Room* destination) : Entity(name, description, (Entity*) origin )
{
}
