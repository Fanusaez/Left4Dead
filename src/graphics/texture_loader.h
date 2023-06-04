#ifndef TEXTURE_LOADER_H
#define TEXTURE_LOADER_H

#include <SDL2pp/SDL2pp.hh>
#include <string>
#include <list>
#include <map>
#include <memory>

typedef std::shared_ptr <SDL2pp::Texture> TexturePtr;

class TextureLoader {
	std::map <std::string, TexturePtr> textures;

public:
	static TextureLoader &getInstance();

	/*
	 * Load all sprites in the spriteNames list.
	 * Each sprite name should be relative to the assets directory.
	 * renderer is the rendering context.
	 */
	void load(SDL2pp::Renderer &renderer, const std::list <std::string> &spriteNames);

	/*
	 * Return a smart pointer to the texture with name spriteName.
	 * The sprite name should be relative to the assets directory.
	 */
	TexturePtr getTexture(const std::string &spriteName);

private:
	TextureLoader();

	~TextureLoader();
};

#endif //TEXTURE_LOADER_H
