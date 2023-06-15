#ifndef TEXTURE_LOADER_H
#define TEXTURE_LOADER_H

#include <SDL2pp/SDL2pp.hh>
#include <string>
#include <list>
#include <map>
#include <memory>

typedef std::shared_ptr <SDL2pp::Texture> TexturePtr;
typedef std::shared_ptr<SDL2pp::Music> MusicPtr;
typedef std::shared_ptr<SDL2pp::Chunk> ChunkPtr;
typedef std::shared_ptr<SDL2pp::Font> FontPtr;

class TextureLoader {
	std::map <std::string, TexturePtr> textures;

	std::map<std::string, MusicPtr> music;

	std::map<std::string, ChunkPtr> chunks;

	std::map<std::string, FontPtr> fonts;

public:
	static TextureLoader &getInstance();

	/*
	 * Load all sprites in the spriteNames list.
	 * Each sprite name should be relative to the assets directory.
	 * renderer is the rendering context.
	 */
	void load(SDL2pp::Renderer &renderer, const std::list <std::string> &spriteNames);

	void loadMusic(const std::list <std::string> &musicNames);

	void loadSFX(const std::list <std::string> &sfxNames);

	void loadFonts(const std::list<std::string> &fontNames);

	/*
	 * Return a smart pointer to the texture with name spriteName.
	 * The sprite name should be relative to the assets directory.
	 */
	TexturePtr getTexture(const std::string &spriteName);

	MusicPtr getMusic(const std::string &musicName);

	ChunkPtr getChunk(const std::string &chunkName);

	FontPtr getFont(const std::string &fontName);

private:
	TextureLoader();

	~TextureLoader();
};

#endif //TEXTURE_LOADER_H
