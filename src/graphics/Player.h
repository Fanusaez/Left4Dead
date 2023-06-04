#ifndef __WORM_H__
#define __WORM_H__

#include <SDL2pp/SDL2pp.hh>
#include "Animation.h"
#include "renderable_object.h"
#include <utility>

class Player : public RenderableObject {
	Animation an;
	bool facingLeft;
	bool moving;

public:
	Player(SDL2pp::Texture &texture, int id, int initialX, int initialY);

	virtual ~Player();

	virtual void updateState(const SoldierObjectDTO &soldierDTO) override;

	virtual void updateState(const ZombieObjectDTO &zombieDTO) override;

	virtual void update(unsigned dt) override;

	virtual void render(SDL2pp::Renderer &renderer, SDL2pp::Rect &dst) override;

private:
	bool isMoving() const;
};

#endif // __WORM_H__