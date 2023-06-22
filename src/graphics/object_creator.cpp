#include "object_creator.h"
#include "Player.h"
#include "scout.h"
#include "infected.h"
#include "witch.h"
#include "jumper.h"
#include "lancer.h"
#include "grenade.h"
#include "smoke.h"

std::unique_ptr<RenderableObject> ObjectCreator::create(const SoldierObjectDTO &soldierDTO) const
{
	if (soldierDTO.soldier_type == SCOUT)
		return std::unique_ptr<RenderableObject>(
			new Scout(soldierDTO.id, soldierDTO.position_x, soldierDTO.position_y,
				   soldierDTO.health, soldierDTO.bullets, soldierDTO.time_smoke_grenade));
	else
		return std::unique_ptr<RenderableObject>(
			new Player(soldierDTO.id, soldierDTO.position_x, soldierDTO.position_y,
				   soldierDTO.health, soldierDTO.bullets, soldierDTO.time_explosive_grenade));
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
	if (grenadeDTO.grenade_type == EXPLOSIVE_GRENADE)
		return std::unique_ptr<RenderableObject>(
			new Grenade(grenadeDTO.id, grenadeDTO.position_x, grenadeDTO.position_y));
	else
		return std::unique_ptr<RenderableObject>(
			new Smoke(grenadeDTO.id, grenadeDTO.position_x, grenadeDTO.position_y));
}
