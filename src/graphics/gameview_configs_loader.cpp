#include "gameview_configs_loader.h"

// 25 fps
#define FRAME_RATE_ 40000

GameviewConfigurationsLoader &GameviewConfigurationsLoader::getInstance()
{
	static GameviewConfigurationsLoader instance;
	return instance;
}

GameviewConfigurationsLoader::GameviewConfigurationsLoader() :
	FRAME_RATE(FRAME_RATE_)
{
	this->setSpritesToLoad();
	this->setMusicToLoad();
	this->setChunksToLoad();
}

const std::list <std::string> &GameviewConfigurationsLoader::getSpritesToLoad()
{
	return this->spritesToLoad;
}

const std::list <std::string> &GameviewConfigurationsLoader::getMusicToLoad()
{
	return this->musicToLoad;
}

const std::list <std::string> &GameviewConfigurationsLoader::getChunksToLoad()
{
	return this->chunksToLoad;
}

const std::list <std::string> GameviewConfigurationsLoader::getSceneSprites() const
{
	std::list<std::string> sceneSprites;
	sceneSprites.push_back("backgrounds/War1/Pale/Full_Sky.png");
	sceneSprites.push_back("backgrounds/War1/Pale/Far_Background.png");
	sceneSprites.push_back("backgrounds/War1/Pale/Floor.png");
	return sceneSprites;
}

void GameviewConfigurationsLoader::setSpritesToLoad()
{
	this->spritesToLoad.push_back("Soldier_1/Walk.png");
	this->spritesToLoad.push_back("Soldier_1/Idle.png");
	this->spritesToLoad.push_back("Soldier_1/Shot_1.png");
	this->spritesToLoad.push_back("Soldier_1/Recharge.png");
	this->spritesToLoad.push_back("Soldier_1/Hurt.png");
	this->spritesToLoad.push_back("Soldier_1/Dead.png");
	this->spritesToLoad.push_back("backgrounds/War1/Pale/Full_Sky.png");
	this->spritesToLoad.push_back("backgrounds/War1/Pale/Far_Background.png");
	this->spritesToLoad.push_back("backgrounds/War1/Pale/Floor.png");
	this->spritesToLoad.push_back("Zombie/Idle.png");
	this->spritesToLoad.push_back("Zombie/Walk.png");
	this->spritesToLoad.push_back("Zombie/Run.png");
	this->spritesToLoad.push_back("Zombie/Jump.png");
	this->spritesToLoad.push_back("Zombie/Attack_1.png");
	this->spritesToLoad.push_back("Zombie/Hurt.png");
	this->spritesToLoad.push_back("Zombie/Dead.png");
	this->spritesToLoad.push_back("Witch/Attack_1.png");
	this->spritesToLoad.push_back("Witch/Idle.png");
	this->spritesToLoad.push_back("Witch/Jump.png");
	this->spritesToLoad.push_back("Witch/Scream.png");
	this->spritesToLoad.push_back("Witch/Walk.png");
	this->spritesToLoad.push_back("Witch/Run.png");
	this->spritesToLoad.push_back("Witch/Hurt.png");
	this->spritesToLoad.push_back("Witch/Dead.png");
	this->spritesToLoad.push_back("Jumper/Idle.png");
	this->spritesToLoad.push_back("Jumper/Walk.png");
	this->spritesToLoad.push_back("Jumper/Run.png");
	this->spritesToLoad.push_back("Jumper/Jump.png");
	this->spritesToLoad.push_back("Jumper/Hurt.png");
	this->spritesToLoad.push_back("Jumper/Dead.png");
	this->spritesToLoad.push_back("Jumper/Attack_1.png");
}

void GameviewConfigurationsLoader::setMusicToLoad()
{
	this->musicToLoad.push_back("Music/10. no way back.flac");
}

void GameviewConfigurationsLoader::setChunksToLoad()
{
	this->chunksToLoad.push_back("Soldier_1/Dead.mp3");
	this->chunksToLoad.push_back("Soldier_1/Recharge.mp3");
	this->chunksToLoad.push_back("Soldier_1/Shot_1.mp3");
	this->chunksToLoad.push_back("Soldier_1/Walk.mp3");
	this->chunksToLoad.push_back("Jumper/Attack_1.mp3");
	this->chunksToLoad.push_back("Jumper/Dead.mp3");
	this->chunksToLoad.push_back("Jumper/Hurt.mp3");
	this->chunksToLoad.push_back("Jumper/Jump.mp3");
	this->chunksToLoad.push_back("Witch/Attack_1.mp3");
	this->chunksToLoad.push_back("Witch/Dead.mp3");
	this->chunksToLoad.push_back("Witch/Hurt.mp3");
	this->chunksToLoad.push_back("Witch/Scream.mp3");
	this->chunksToLoad.push_back("Zombie/Dead.mp3");
	this->chunksToLoad.push_back("Zombie/Hurt.mp3");
}

GameviewConfigurationsLoader::~GameviewConfigurationsLoader() = default;
