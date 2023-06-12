#ifndef GAMEVIEW_CONFIGS_LOADER_H
#define GAMEVIEW_CONFIGS_LOADER_H

#include <list>
#include <string>

class GameviewConfigurationsLoader {
public:
	static GameviewConfigurationsLoader &getInstance();

	GameviewConfigurationsLoader(const GameviewConfigurationsLoader &) = delete;

	GameviewConfigurationsLoader &operator=(const GameviewConfigurationsLoader &) = delete;

	GameviewConfigurationsLoader(GameviewConfigurationsLoader &&) = delete;

	GameviewConfigurationsLoader &operator=(GameviewConfigurationsLoader &&) = delete;

	const unsigned FRAME_RATE;

	const std::list <std::string> &getSpritesToLoad();

	const std::list <std::string> &getMusicToLoad();

	const std::list <std::string> &getChunksToLoad();

	const std::list<std::string> getSceneSprites() const;

private:
	GameviewConfigurationsLoader();

	~GameviewConfigurationsLoader();

	std::list <std::string> spritesToLoad;

	std::list<std::string> musicToLoad;

	std::list<std::string> chunksToLoad;
};

#endif //GAMEVIEW_CONFIGS_LOADER_H
