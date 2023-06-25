#ifndef GRAPHICS_P90_SOLDIER_H
#define GRAPHICS_P90_SOLDIER_H

#include "renderable_object.h"
#include "playable.h"
#include "texture_loader.h"
#include "Animation.h"
#include "../common/game_object_state.h"

class SoldierP90 : public Playable {
	TextureLoader &textureLoader;
	Animation animation;
	bool facingLeft;
	SoldierObjectState state;
	std::shared_ptr<SDL2pp::Chunk> sfx;
	int sfxLoops;
	bool playSFX;
	int lastChannel;

public:
	SoldierP90(const SoldierObjectDTO &soldierDTO);

	virtual ~SoldierP90();

	virtual void updateState(const SoldierObjectDTO &soldierDTO) override;

	virtual void updateState(const ZombieObjectDTO &zombieDTO) override;

	virtual void updateState(const GrenadeObjectDTO &grenadeDTO) override;

	virtual void update(unsigned dt) override;

	virtual void render(SDL2pp::Renderer &renderer, SDL2pp::Rect &dst) override;

	virtual void renderAudio(SDL2pp::Mixer &mixer) override;

private:
	void changeState(const SoldierObjectState &state);
};

#endif //GRAPHICS_P90_SOLDIER_H
