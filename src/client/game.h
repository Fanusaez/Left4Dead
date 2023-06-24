#ifndef LEFT4DEAD_GAME_H
#define LEFT4DEAD_GAME_H

#include "client.h"

#include "../graphics/gameview.h"
#include "../graphics/texture_loader.h"
#include "../graphics/gameview_configs_loader.h"
#include "../graphics/renderable_object.h"
#include "../graphics/object_creator.h"

#include "../common/game_dto.h"

#include <map>
#include <memory>

class MainGame {
	int player_id;
	Client client;
	GameviewConfigurationsLoader &configs;
	TextureLoader &textureLoader;
	std::map<int, std::unique_ptr<RenderableObject>> objects;
	Gameview view;
	double rate;
	inline static SDL2pp::SDLTTF ttf;
	int eventTimestamp;

public:
	MainGame(int id, Socket &socket);

	~MainGame();

	void start();

private:
	bool handleEvents();

	bool handleQuitGame();

	void doMainGameLogic(GameDTO &gameState, ObjectCreator &creator, bool &running, bool &end_game);

	void doGameOverLogic(GameDTO &gameState, bool &running);
};

#endif //LEFT4DEAD_GAME_H
