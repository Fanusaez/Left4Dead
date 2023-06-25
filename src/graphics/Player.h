#ifndef __WORM_H__
#define __WORM_H__

#include <SDL2pp/SDL2pp.hh>
#include "Animation.h"
#include "renderable_object.h"
#include "playable.h"
#include "texture_loader.h"
#include "../common/game_object_state.h"
#include <utility>

class Player : public Playable {
	TextureLoader &textureLoader;
	Animation an;
	bool facingLeft;
	SoldierObjectState state;
	std::shared_ptr<SDL2pp::Chunk> sfx;
	int sfxLoops;
	bool playSFX;
	int lastChannel;

public:
	Player(const SoldierObjectDTO &soldierDTO);

	virtual ~Player();

	virtual void updateState(const SoldierObjectDTO &soldierDTO) override;

	virtual void updateState(const ZombieObjectDTO &zombieDTO) override;

	virtual void updateState(const GrenadeObjectDTO &grenadeDTO) override;

	virtual void update(unsigned dt) override;

	virtual void render(SDL2pp::Renderer &renderer, SDL2pp::Rect &dst) override;

	virtual void renderAudio(SDL2pp::Mixer &mixer) override;

private:
	bool isMoving() const;

	void changeState(const SoldierObjectState &state);
};

#endif // __WORM_H__