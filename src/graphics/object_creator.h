#ifndef CLIENT_CREATOR_H
#define CLIENT_CREATOR_H

#include "renderable_object.h"
#include "../common/game_dto.h"
#include <memory>

class ObjectCreator {
public:
	std::unique_ptr<RenderableObject> create(const SoldierObjectDTO &soldierDTO) const;
	std::unique_ptr<RenderableObject> create(const ZombieObjectDTO &zombieDTO) const;
};

#endif //CLIENT_CREATOR_H
