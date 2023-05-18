#ifndef LEFT4DEAD_BACKGROUND_H
#define LEFT4DEAD_BACKGROUND_H

#include <SDL2pp/SDL2pp.hh>

#ifndef FRAME_RATE
#define FRAME_RATE 1000000.0f/25.0f
#endif

class Background {
	SDL2pp::Texture &texture;

	int scrollingOffset;

	int speed;

	float elapsed;

public:
	Background(SDL2pp::Texture &backgroundTexture);

	void moveLeft();

	void moveRight();

	void stop();

    	void update(float dt);

	void render(SDL2pp::Renderer &renderer);

	~Background();

private:
	void renderMovedLeft(SDL2pp::Renderer &renderer);

	void renderMovedRight(SDL2pp::Renderer &renderer);
};

#endif //LEFT4DEAD_BACKGROUND_H
