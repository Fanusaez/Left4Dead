#ifndef LEFT4DEAD_STAGE_H
#define LEFT4DEAD_STAGE_H

#include <SDL2pp/SDL2pp.hh>
#include "texture_loader.h"
#include <string>

#ifndef FRAME_RATE
#define FRAME_RATE 1000000.0f/25.0f
#endif

class Stage {
	SDL2pp::Texture &skyTexture;

	SDL2pp::Texture &backgroundTexture;

	SDL2pp::Texture &floorTexture;

	int backgroundOffset;

	int backgroundSpeed;

	int floorOffset;

	int floorSpeed;

	float elapsed;

public:
	Stage(SDL2pp::Texture &skyTexture, SDL2pp::Texture &backgroundTexture, SDL2pp::Texture &floorTexture);

	void moveLeft();

	void moveRight();

	void stop();

    	void update(float dt);

	void render(SDL2pp::Renderer &renderer);

	~Stage();

private:
	void render(SDL2pp::Renderer &renderer, SDL2pp::Texture &texture, int &offset);

	void renderMovedLeft(SDL2pp::Renderer &renderer, SDL2pp::Texture &texture, int offset);

	void renderMovedRight(SDL2pp::Renderer &renderer, SDL2pp::Texture &texture, int offset);
};

#endif //LEFT4DEAD_STAGE_H
