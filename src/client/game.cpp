#include "game.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "../graphics/scene.h"

#include <utility>
#include <optional>
#include <set>
#include <vector>
#include <chrono>
#include <sstream>

MainGame::MainGame(int id, Socket &socket) :
	player_id(id),
	client(std::move(socket)),
	configs(GameviewConfigurationsLoader::getInstance()),
	textureLoader(TextureLoader::getInstance()),
	objects(),
	view(this->objects),
	rate(0.04)
{
	this->textureLoader.load(this->view.getRenderer(), this->configs.getSpritesToLoad());
	this->textureLoader.loadMusic(this->configs.getMusicToLoad());
	this->textureLoader.loadSFX(this->configs.getChunksToLoad());
	this->textureLoader.loadFonts(this->configs.getFontsToLoad());
	std::unique_ptr<Scene> scene(new Scene());
	this->view.setScene(scene);
}

MainGame::~MainGame()
{
	this->client.join();
}

void MainGame::start()
{
	bool running = true;
	bool end_game = true;
	GameDTO gameState;
	ObjectCreator creator;

	while (running) {
		auto t_start = std::chrono::high_resolution_clock::now();
		std::optional<GameDTO> gameOptional = this->client.get_game();
		if (gameOptional.has_value())
			gameState = gameOptional.value();

		if (not gameState.is_end_game())
			this->doMainGameLogic(gameState, creator, running, end_game);
		else
			this->doGameOverLogic(gameState, running);

		auto t_end = std::chrono::high_resolution_clock::now();
		std::chrono::duration<double> duration = t_end - t_start;
		double seconds = duration.count();
		double rest = this->rate - seconds;
		if(rest < 0) {
			double behind = -rest;
			double lost = behind - std::fmod(behind, this->rate);
			t_start += std::chrono::duration_cast<std::chrono::high_resolution_clock::duration>(std::chrono::duration<double>(lost));
		} else {
			std::this_thread::sleep_for(std::chrono::duration<double>(rest));
		}
	}
}

void MainGame::doMainGameLogic(GameDTO &gameState, ObjectCreator &creator, bool &running, bool &end_game)
{
	std::set<int> idsToKeep;
	std::vector<SoldierObjectDTO> soldiers = gameState.get_soldiers();
	for (auto& soldier: soldiers){
		idsToKeep.insert(soldier.id);
		if(objects.find(soldier.id) == objects.end()) {
			std::unique_ptr<RenderableObject> ptr = std::move(creator.create(soldier));
			objects[ptr->getID()] = std::move(ptr);
			if (soldier.player_id == player_id)
				view.assignMainObject(soldier.id);
		} else {
			RenderableObject &object = *(objects.at(soldier.id));
			object.updateState(soldier);
		}
	}
	std::vector<ZombieObjectDTO> zombies = gameState.get_zombies();
	for (auto& zombie: zombies){
		idsToKeep.insert(zombie.id);
		if(objects.find(zombie.id) == objects.end()) {
			std::unique_ptr<RenderableObject> ptr = std::move(creator.create(zombie));
			objects[ptr->getID()] = std::move(ptr);
		} else {
			RenderableObject &object = *(objects.at(zombie.id));
			object.updateState(zombie);
		}
	}
	std::vector<GrenadeObjectDTO> elements = gameState.get_elements();
	for (auto &element: elements) {
		idsToKeep.insert(element.id);
		if (objects.find(element.id) == objects.end()) {
			std::unique_ptr <RenderableObject> ptr = std::move(creator.create(element));
			objects[ptr->getID()] = std::move(ptr);
		}
	}

	for (auto it = objects.begin(); it != objects.end(); ) {
		if (idsToKeep.count(it->first) == 0) {
			it = objects.erase(it);
		} else {
			it->second->update(configs.FRAME_RATE);
			++it;
		}
	}
	this->view.render();
	running = this->handleEvents();
}

void MainGame::doGameOverLogic(GameDTO &gameState, bool &running)
{
	GameStats stats = gameState.get_game_stats();
	this->view.renderGameOver(stats.total_bullets, stats.total_dead_zombies);
	running = this->handleQuitGame();
}

bool MainGame::handleEvents()
{
	SDL_Event event;
	while (SDL_PollEvent(&event) != 0) {
		switch (event.type) {
			case SDL_KEYDOWN: {
				SDL_KeyboardEvent &keyEvent = event.key;
				switch (keyEvent.keysym.sym) {
					case SDLK_LEFT: {
						if (keyEvent.repeat == 0) {
							this->client.move(LEFT);
						}
						break;
					}
					case SDLK_RIGHT: {
						if (keyEvent.repeat == 0) {
							this->client.move(RIGHT);
						}
						break;
					}
					case SDLK_UP: {
						if (keyEvent.repeat == 0) {
							this->client.move(UP);
						}
						break;
					}
					case SDLK_DOWN: {
						if (keyEvent.repeat == 0) {
							this->client.move(DOWN);
						}
						break;
					}
					case SDLK_r: {
						if (keyEvent.repeat == 0) {
							this->client.reload();
						}
						break;
					}
					case SDLK_s: {
						if (keyEvent.repeat == 0) {
							this->client.shoot();
						}
						break;
					}
					case SDLK_e: {
						if (keyEvent.repeat == 0) {
							this->client.revive_soldier();
						}
						break;
					}
				}
			} // Fin KEY_DOWN
				break;
			case SDL_KEYUP: {
				SDL_KeyboardEvent &keyEvent = event.key;
				switch (keyEvent.keysym.sym) {
					case SDLK_LEFT: {
						this->client.move(STOP_MOVE);
						break;
					}
					case SDLK_RIGHT: {
						this->client.move(STOP_MOVE);
						break;
					}
					case SDLK_UP: {
						this->client.move(STOP_MOVE);
						break;
					}
					case SDLK_DOWN: {
						this->client.move(STOP_MOVE);
						break;
					}
					case SDLK_s: {
						this->client.move(STOP_MOVE);
						break;
					}
					case SDLK_PLUS: {
						this->view.increaseVolume();
						break;
					}
					case SDLK_MINUS: {
						this->view.lowerVolume();
						break;
					}
					case SDLK_p: {
						this->view.pauseMusic();
						break;
					}
					case SDLK_o: {
						this->view.resumeMusic();
						break;
					}
					case SDLK_q: {
						int8_t delta = 1;
						this->client.throw_explosive_grenade(delta);
						break;
					}
					case SDLK_w: {
						int8_t delta = 10;
						this->client.throw_smoke_grenade(delta);
						break;
					}
					case SDLK_a: {
						int8_t delta = 10;
						this->client.call_air_strike();
						break;
					}
				}
			} // Fin KEY_UP
				break;
			case SDL_QUIT:
				return false;
		} // fin switch(event)
	}	  // fin while(SDL_PollEvents)
	return true;
}

bool MainGame::handleQuitGame()
{
	SDL_Event event;
	while (SDL_PollEvent(&event) != 0) {
		if (event.type == SDL_QUIT)
			return false;
	}
	return true;
}
