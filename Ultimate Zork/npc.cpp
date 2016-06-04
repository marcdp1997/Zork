#include "Player.h"
#include "Path.h"
#include "Item.h"
#include "Room.h"
#include "Npc.h"

#include <stdlib.h>
#include <time.h>  

Npc::Npc(const char* name, const char* description, Room* c_pos) : Creature(name, description, c_pos, 4, 20, 2)
{
	type = NPC;
	inventory = nullptr;
	st_step = WALK;
}

Npc::~Npc()
{}

// We will enter this method as goblin so we need the player stats to do the combat.
void Npc::Update(Vector<Entity*>& Entities, Player* p, uint i)
{
	if (p->curr_pos == curr_pos && st_step == WALK) st_step = COMBAT;

	switch (st_step)
	{
	case WALK:
		Move(Entities);
		break;
	case COMBAT:
		Combat(Entities, p, i);
	}
}

void Npc::Move(const Vector<Entity*>& Entities)
{
	srand(time(NULL));

	for (int j = 0; j < Entities.num_elements; j++)
	{
		Entity* aux = Entities[j];

		if (aux->type == PATH)
		{
			Path* p = (Path*)aux;
			int decision = rand() % 10;

			// The enemy is in each room a different period of time because of the condition.
			if (p->source == curr_pos && decision == 1 && p->destination->name != "Dunedin Gates")
				curr_pos = p->destination;
		}
	}
}

void Npc::Combat(Vector<Entity*>& Entities, Player* p, uint i)
{
	printf("\n%s has appeared in the same area than you.\nYou must fight with him to move!\n", name.string);

	while (p->hp > 0 && hp > 0)
	{
		Player_Attack(p);
		Goblin_Attack(p);
	}

	if (p->hp == 0) printf("You are dead!\nGAME OVER\n\n");
	if (hp == 0)
	{
		printf("You have defeated %s. +%i coins!\n\n", name.string, coins);
		Entities.pop(i);
	}
}

void Npc::Player_Attack(Player* p)
{
	uint delay = 0;
	while (delay != 800000000)
		delay++;

	if (hp > p->damage) hp -= p->damage;
	else
	{
		hp = 0;
		p->coins += coins;
	}

	if (p->weapon != nullptr) printf("You attack %s for %i with your %s! %s has %i left.\n", name.string, p->damage, p->weapon->name.string, name.string, hp);
	else printf("You punch %s for %i! %s has %i left.\n", name.string, p->damage, name.string, hp);

}

void Npc::Goblin_Attack(Player* p)
{
	uint delay = 0;
	while (delay != 800000000)
		delay++;

	if (p->hp > damage) p->hp -= damage;
	else p->hp = 0;

	printf("%s attack you for %i! You have %i HP left.\n", name.string, damage, p->hp);
}