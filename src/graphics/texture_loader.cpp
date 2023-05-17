#include "texture_loader.h"
#include <utility>

static const std::string AssetsPath = ASSETS_PATH;

TextureLoader::TextureLoader() {}

void TextureLoader::load(SDL2pp::Renderer &renderer, const std::list <std::string> &spriteNames)
{
	for (auto const &sprite: spriteNames) {
		SDL2pp::Texture im(renderer, SDL2pp::Surface(std::string(AssetsPath).append(sprite)).SetColorKey(true, 0));
		this->textures[sprite] = std::make_unique<SDL2pp::Texture>(std::move(im));
	}
}

/*
 * Note that this reference is not const and might be shared by
 * many objects.
 * This is because the Renderer:Copy() method doesn't accept a const reference to
 * the texture.
 */
SDL2pp::Texture &TextureLoader::getTexture(const std::string &spriteName)
{
	return *(this->textures.at(spriteName));
}

TextureLoader::~TextureLoader() = default;
