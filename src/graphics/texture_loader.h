#ifndef TEXTURE_LOADER_H
#define TEXTURE_LOADER_H

#include <SDL2pp/SDL2pp.hh>
#include <string>
#include <list>
#include <map>
#include <memory>

typedef std::unique_ptr<SDL2pp::Texture> TexturePtr;

class TextureLoader {
	std::map<std::string, TexturePtr> textures;

public:
	TextureLoader();

	/*
	 * Load all sprites in the spriteNames list.
	 * Each sprite name should be relative to the assets directory.
	 * renderer is the rendering context.
	 */
    	void load(SDL2pp::Renderer &renderer, const std::list<std::string> &spriteNames);

	/*
	 * Return a reference to the texture with name spriteName.
	 * The sprite name should be relative to the assets directory.
	 */
	SDL2pp::Texture &getTexture(const std::string &spriteName);

	~TextureLoader();
};

#endif //TEXTURE_LOADER_H