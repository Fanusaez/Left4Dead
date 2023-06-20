#include "object_creator.h"
#include "Player.h"
#include "infected.h"
#include "witch.h"
#include "jumper.h"
#include "lancer.h"
#include "grenade.h"

std::unique_ptr<RenderableObject> ObjectCreator::create(const SoldierObjectDTO &soldierDTO) const
{
	return std::unique_ptr<RenderableObject>(
		new Player(soldierDTO.id,
			   soldierDTO.position_x, soldierDTO.position_y,
			   soldierDTO.health, soldierDTO.bullets));
}

std::unique_ptr<RenderableObject> ObjectCreator::create(const ZombieObjectDTO &zombieDTO) const
{
	if (zombieDTO.zombie_type == INFECTED)
		return std::unique_ptr<RenderableObject>(
			new Infected(zombieDTO.id, zombieDTO.position_x, zombieDTO.position_y));
	else if (zombieDTO.zombie_type == JUMPER)
		return std::unique_ptr<RenderableObject>(
			new Jumper(zombieDTO.id, zombieDTO.position_x, zombieDTO.position_y));
	else if (zombieDTO.zombie_type == SPEAR)
		return std::unique_ptr<RenderableObject>(
			new Lancer(zombieDTO.id, zombieDTO.position_x, zombieDTO.position_y));
	else
		return std::unique_ptr<RenderableObject>(
			new Witch(zombieDTO.id, zombieDTO.position_x, zombieDTO.position_y));
		
}

std::unique_ptr <RenderableObject> ObjectCreator::create(const GrenadeObjectDTO &grenadeDTO) const
{
	return std::unique_ptr<RenderableObject>(
		new Grenade(grenadeDTO.id, grenadeDTO.position_x, grenadeDTO.position_y));
}
