#ifndef LEFT4DEAD_SCENE_H
#define LEFT4DEAD_SCENE_H

#include <SDL2pp/SDL2pp.hh>
#include "texture_loader.h"
#include <string>

class Scene {
	TexturePtr skyTexture;
	TexturePtr backgroundTexture;
	TexturePtr floorTexture;
	int offset;

public:
	Scene();

	void increaseOffset(int newOffset);

	void render(SDL2pp::Renderer &renderer);

	~Scene();

private:
	void render(SDL2pp::Renderer &renderer, SDL2pp::Texture &texture, int offset);

	void renderMovedLeft(SDL2pp::Renderer &renderer, SDL2pp::Texture &texture, int offset);

	void renderMovedRight(SDL2pp::Renderer &renderer, SDL2pp::Texture &texture, int offset);
};

#endif //LEFT4DEAD_SCENE_H
