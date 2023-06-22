#ifndef RENDERABLE_OBJECT_H
#define RENDERABLE_OBJECT_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2pp/SDL2pp.hh>
#include "../common/game_dto.h"

class RenderableObject {
	int id_;

protected:
	int xPosition;

	int yPosition;

public:
	RenderableObject(int id, int initialX, int initialY);

	virtual void updateState(const SoldierObjectDTO &soldierDTO) = 0;

	virtual void updateState(const ZombieObjectDTO &zombieDTO) = 0;

	virtual void updateState(const GrenadeObjectDTO &grenadeDTO) = 0;

	virtual void update(unsigned dt) = 0;

	virtual void render(SDL2pp::Renderer &renderer, SDL2pp::Rect &dst) = 0;

	virtual void renderAudio(SDL2pp::Mixer &mixer) = 0;

	int getID() const;

	int getPositionX() const;

	int getPositionY() const;

	void setPositionX(int x);

	void setPositionY(int y);

	virtual bool isPlayable() const;

	virtual ~RenderableObject();
};

#endif //RENDERABLE_OBJECT_H
