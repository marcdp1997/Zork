#include "Entity.h"

Entity::Entity(const char* name, const char* description) : name(name), description(description)
{
	type = ENTITY;
}

Entity::~Entity()
{}