#include "gameview_configs_loader.h"

// 25 fps
#define FRAME_RATE_ 40000

GameviewConfigurationsLoader &GameviewConfigurationsLoader::getInstance() {
	static GameviewConfigurationsLoader instance;
	return instance;
}

GameviewConfigurationsLoader::GameviewConfigurationsLoader() :
	FRAME_RATE(FRAME_RATE_) {
	this->spritesToLoad.push_back("Soldier_1/Walk.png");
	this->spritesToLoad.push_back("backgrounds/War1/Pale/Full_Sky.png");
	this->spritesToLoad.push_back("backgrounds/War1/Pale/Far_Background.png");
	this->spritesToLoad.push_back("backgrounds/War1/Pale/Floor.png");
}

const std::list <std::string> &GameviewConfigurationsLoader::getSpritesToLoad() {
	return this->spritesToLoad;
}

GameviewConfigurationsLoader::~GameviewConfigurationsLoader() = default;