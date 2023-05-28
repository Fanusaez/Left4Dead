#ifndef RENDERABLE_OBJECT_H
#define RENDERABLE_OBJECT_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2pp/SDL2pp.hh>

class RenderableObject {
	int id_;

protected:
	int xPosition;

	int yPosition;

public:
	RenderableObject(int id, int initialX, int initialY);

	virtual void update(unsigned dt) = 0;

	virtual void render(SDL2pp::Renderer &renderer, SDL2pp::Rect &dst) = 0;

	//virtual void renderAudio(SDL2pp::Mixer &mixer) = 0;

	int getID() const;

	int getPositionX() const;

	int getPositionY() const;

	void setPositionX(float position_x);

	void setPositionY(float position_y);

	virtual ~RenderableObject();
};

#endif //RENDERABLE_OBJECT_H
