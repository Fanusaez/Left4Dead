#include "gameview_configs_loader.h"

// 25 fps
#define FRAME_RATE_ 40000

GameviewConfigurationsLoader &GameviewConfigurationsLoader::getInstance() {
	static GameviewConfigurationsLoader instance;
	return instance;
}

GameviewConfigurationsLoader::GameviewConfigurationsLoader() :
	FRAME_RATE(FRAME_RATE_)
{
	this->spritesToLoad.push_back("Soldier_1/Walk.png");
	this->spritesToLoad.push_back("Soldier_1/Idle.png");
	this->spritesToLoad.push_back("Soldier_1/Shot_1.png");
	this->spritesToLoad.push_back("Soldier_1/Recharge.png");
	this->spritesToLoad.push_back("backgrounds/War1/Pale/Full_Sky.png");
	this->spritesToLoad.push_back("backgrounds/War1/Pale/Far_Background.png");
	this->spritesToLoad.push_back("backgrounds/War1/Pale/Floor.png");
	this->spritesToLoad.push_back("Zombie/Idle.png");
	this->spritesToLoad.push_back("Zombie/Walk.png");
	this->spritesToLoad.push_back("Zombie/Run.png");
	this->spritesToLoad.push_back("Zombie/Jump.png");
	this->spritesToLoad.push_back("Zombie/Attack_1.png");
}

const std::list <std::string> &GameviewConfigurationsLoader::getSpritesToLoad() {
	return this->spritesToLoad;
}

const std::list <std::string> GameviewConfigurationsLoader::getSceneSprites() const
{
	std::list<std::string> sceneSprites;
	sceneSprites.push_back("backgrounds/War1/Pale/Full_Sky.png");
	sceneSprites.push_back("backgrounds/War1/Pale/Far_Background.png");
	sceneSprites.push_back("backgrounds/War1/Pale/Floor.png");
	return sceneSprites;
}

GameviewConfigurationsLoader::~GameviewConfigurationsLoader() = default;
