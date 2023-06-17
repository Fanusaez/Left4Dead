#ifndef GRAPHICS_INFECTED_H
#define GRAPHICS_INFECTED_H

#include "renderable_object.h"
#include "texture_loader.h"
#include "Animation.h"
#include "../common/game_object_state.h"

class Infected : public RenderableObject {
	TextureLoader &textureLoader;
	Animation animation;
	bool facingLeft;
	ZombieObjectState state;
	std::shared_ptr<SDL2pp::Chunk> sfx;
	int sfxLoops;
	bool playSFX;
	int lastChannel;

public:
	Infected(int id, int initialX, int initialY);

	virtual ~Infected();

	virtual void updateState(const SoldierObjectDTO &soldierDTO) override;

	virtual void updateState(const ZombieObjectDTO &zombieDTO) override;

	virtual void updateState(const GrenadeObjectDTO &grenadeDTO) override;

	virtual void update(unsigned dt) override;

	virtual void render(SDL2pp::Renderer &renderer, SDL2pp::Rect &dst) override;

	virtual void renderAudio(SDL2pp::Mixer &mixer) override;

private:
	bool isMoving() const;

	void changeState(const ZombieObjectState &state);
};

#endif //GRAPHICS_INFECTED_H
