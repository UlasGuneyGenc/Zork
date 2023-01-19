#pragma once
#include "Entity.h"

class Item : public Entity
{
	Item(const char* name, const char* description, Entity* parent);
};
