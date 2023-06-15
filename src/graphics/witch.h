#ifndef CLIENT_WITCH_H
#define CLIENT_WITCH_H

#include "renderable_object.h"
#include "texture_loader.h"
#include "Animation.h"
#include "../common/game_object_state.h"

class Witch : public RenderableObject {
	TextureLoader &textureLoader;
	Animation animation;
	bool facingLeft;
	ZombieObjectState state;
	std::shared_ptr<SDL2pp::Chunk> sfx;
	int sfxLoops;
	bool playSFX;
	int lastChannel;

public:
	Witch(int id, int initialX, int initialY);

	virtual ~Witch();

	virtual void updateState(const SoldierObjectDTO &soldierDTO) override;

	virtual void updateState(const ZombieObjectDTO &zombieDTO) override;

	virtual void update(unsigned dt) override;

	virtual void render(SDL2pp::Renderer &renderer, SDL2pp::Rect &dst) override;

	virtual void renderAudio(SDL2pp::Mixer &mixer) override;

private:
	bool isMoving() const;

	void changeState(const ZombieObjectState &state);
};

#endif //CLIENT_WITCH_H
