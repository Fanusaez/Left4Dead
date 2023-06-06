#include "object_creator.h"
#include "Player.h"
#include "infected.h"

std::unique_ptr<RenderableObject> ObjectCreator::create(const SoldierObjectDTO &soldierDTO) const
{
	return std::unique_ptr<RenderableObject>(
		new Player(soldierDTO.id, soldierDTO.position_x, soldierDTO.position_y));
}

std::unique_ptr<RenderableObject> ObjectCreator::create(const ZombieObjectDTO &zombieDTO) const
{
	return std::unique_ptr<RenderableObject>(
		new Infected(zombieDTO.id, zombieDTO.position_x, zombieDTO.position_y));
}
