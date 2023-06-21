//
// Created by ignat on 21/06/23.
//

#ifndef GRAPHICS_SMOKE_H
#define GRAPHICS_SMOKE_H

#include "renderable_object.h"
#include "texture_loader.h"
#include "Animation.h"

class Smoke : public RenderableObject {
	TextureLoader &textureLoader;
	Animation animation;
	std::shared_ptr<SDL2pp::Chunk> sfx;
	bool playSFX;
	int lastChannel;

public:
	Smoke(int id, int initialX, int initialY);

	virtual ~Smoke();

	virtual void updateState(const SoldierObjectDTO &soldierDTO) override;

	virtual void updateState(const ZombieObjectDTO &zombieDTO) override;

	virtual void updateState(const GrenadeObjectDTO &grenadeDTO) override;

	virtual void update(unsigned dt) override;

	virtual void render(SDL2pp::Renderer &renderer, SDL2pp::Rect &dst) override;

	virtual void renderAudio(SDL2pp::Mixer &mixer) override;
};

#endif //GRAPHICS_SMOKE_H
