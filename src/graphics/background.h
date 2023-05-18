#ifndef LEFT4DEAD_BACKGROUND_H
#define LEFT4DEAD_BACKGROUND_H

#include <SDL2pp/SDL2pp.hh>

class Background {
	SDL2pp::Texture &texture;

	int scrollingOffset;

public:
	Background(SDL2pp::Texture &backgroundTexture);

	//void moveLeft();

	//void moveRight();

	void render(SDL2pp::Renderer &renderer);

	~Background();
};

#endif //LEFT4DEAD_BACKGROUND_H
