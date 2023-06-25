#include "object_creator.h"
#include "Player.h"
#include "scout.h"
#include "p90_soldier.h"
#include "infected.h"
#include "witch.h"
#include "jumper.h"
#include "lancer.h"
#include "venom.h"
#include "grenade.h"
#include "smoke.h"
#include "venom_grenade.h"

std::unique_ptr<RenderableObject> ObjectCreator::create(const SoldierObjectDTO &soldierDTO) const
{
	if (soldierDTO.soldier_type == SCOUT) {
		return std::unique_ptr<RenderableObject>(
			new Scout(soldierDTO));

	} else if (soldierDTO.soldier_type == P90)
		return std::unique_ptr<RenderableObject>(
			new SoldierP90(soldierDTO));
	else
		return std::unique_ptr<RenderableObject>(
			new Player(soldierDTO));
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
	else if (zombieDTO.zombie_type == VENOM)
		return std::unique_ptr<RenderableObject>(
			new Venom(zombieDTO.id, zombieDTO.position_x, zombieDTO.position_y));
	else
		return std::unique_ptr<RenderableObject>(
			new Witch(zombieDTO.id, zombieDTO.position_x, zombieDTO.position_y));
		
}

std::unique_ptr <RenderableObject> ObjectCreator::create(const GrenadeObjectDTO &grenadeDTO) const
{
	if (grenadeDTO.grenade_type == EXPLOSIVE_GRENADE)
		return std::unique_ptr<RenderableObject>(
			new Grenade(grenadeDTO.id, grenadeDTO.position_x, grenadeDTO.position_y));
	else if (grenadeDTO.grenade_type == VENOM_GRENADE)
		return std::unique_ptr<RenderableObject>(
			new VenomGrenade(grenadeDTO.id, grenadeDTO.position_x, grenadeDTO.position_y));
	else
		return std::unique_ptr<RenderableObject>(
			new Smoke(grenadeDTO.id, grenadeDTO.position_x, grenadeDTO.position_y));
}
