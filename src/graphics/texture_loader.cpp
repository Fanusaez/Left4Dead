#include "texture_loader.h"
#include <utility>

static const std::string AssetsPath = ASSETS_PATH;

TextureLoader::TextureLoader() {}

TextureLoader &TextureLoader::getInstance() {
	static TextureLoader instance;
	return instance;
}

void TextureLoader::load(SDL2pp::Renderer &renderer, const std::list <std::string> &spriteNames) {
	for (auto const &sprite: spriteNames) {
		SDL2pp::Texture im(renderer,
				   SDL2pp::Surface(std::string(AssetsPath).append(sprite)).SetColorKey(true, 0));
		this->textures[sprite] = std::make_shared<SDL2pp::Texture>(std::move(im));
	}
}

void TextureLoader::loadMusic(const std::list <std::string> &musicNames)
{
	for (auto const &musicFile: musicNames) {
		SDL2pp::Music mu(std::string(AssetsPath).append(musicFile));
		this->music[musicFile] = std::make_shared<SDL2pp::Music>(std::move(mu));
	}
}

void TextureLoader::loadSFX(const std::list <std::string> &sfxNames)
{
	for (auto const &chunkFile: sfxNames) {
		SDL2pp::Chunk sfx(std::string(AssetsPath).append(chunkFile));
		this->chunks[chunkFile] = std::make_shared<SDL2pp::Chunk>(std::move(sfx));
	}
}

/*
 * Note that this reference is not const and might be shared by
 * many objects.
 * This is because the Renderer:Copy() method doesn't accept a const reference to
 * the texture.
 */
TexturePtr TextureLoader::getTexture(const std::string &spriteName)
{
	TexturePtr ptr = this->textures.at(spriteName);
	return ptr;
}

MusicPtr TextureLoader::getMusic(const std::string &musicName)
{
	MusicPtr ptr = this->music.at(musicName);
	return ptr;
}

ChunkPtr TextureLoader::getChunk(const std::string &chunkName)
{
	ChunkPtr ptr = this->chunks.at(chunkName);
	return ptr;
}

TextureLoader::~TextureLoader() = default;
