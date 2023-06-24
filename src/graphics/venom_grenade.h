#ifndef GRAPHICS_VENOM_GRENADE_H
#define GRAPHICS_VENOM_GRENADE_H

#include "renderable_object.h"
#include "texture_loader.h"
#include "Animation.h"

class VenomGrenade : public RenderableObject {
	TextureLoader &textureLoader;
	Animation animation;
	std::shared_ptr<SDL2pp::Chunk> sfx;
	bool playSFX;
	int lastChannel;

public:
	VenomGrenade(int id, int initialX, int initialY);

	~VenomGrenade();

	virtual void updateState(const SoldierObjectDTO &soldierDTO) override;

	virtual void updateState(const ZombieObjectDTO &zombieDTO) override;

	virtual void updateState(const GrenadeObjectDTO &grenadeDTO) override;

	virtual void update(unsigned dt) override;

	virtual void render(SDL2pp::Renderer &renderer, SDL2pp::Rect &dst) override;

	virtual void renderAudio(SDL2pp::Mixer &mixer) override;
};

#endif //GRAPHICS_VENOM_GRENADE_H
