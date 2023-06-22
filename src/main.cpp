#include <iostream>
#include "client.h"
#include "lobby.h"

/* Graphics */
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
//#include <SDL2pp/SDL2pp.hh>
#include "graphics/gameview.h"
#include "graphics/texture_loader.h"
#include "graphics/gameview_configs_loader.h"
#include "graphics/scene.h"
#include "graphics/object_creator.h"

#include <iostream>
#include <exception>
#include <unistd.h>
#include <string>
#include <list>
#include <set>
#include <map>
#include <memory>
#include <optional>
#include <chrono>
#include <sstream>

static bool handleEvents(Client* client, Gameview &view);
double rate = 0.04;

int main(int argc, char *argv[])
{
	/*
	Gameloop donde estoy en el lobby. Todo el tiempo estoy chequeando nuevos mensajes de server 
	ya sea por el create o el join o la lista de partidas o el chat
	*/
	Lobby lobby(argv[1], argv[2]);
	int32_t player_id = lobby.get_player_id();
	while (lobby.running()) {
		std::string input;
		std::getline(std::cin, input);

		std::istringstream iss(input);
		std::string mode;
		iss >> mode;

		if (mode == "create") {
			std::string map;
			iss >> map;
			lobby.create_scenario(map);
		} else if (mode == "join") {
			if (iss.eof()) {
				std::cout<<"Error: se requiere un código para unirse a un escenario."<<std::endl;
				continue;  // Vuelve al inicio del bucle
        	}
			int32_t code;
			iss >> code;
			lobby.join_scenario(code);
		} else if (mode == "start") {
			lobby.start();
		} else if (mode == "quit") {
			lobby.close();
			return 0;
		}
		lobby.update();
	}
	// TODO: probar algo mejor
	/*
	 * Antes tenia el ttf en el gameview pero se destruia antes que el textureloader,
	 * entonces el texture loader no podia destruir fonts, porque la clase Font
	 * depende de que la libreria SDLTTF este inicializada.
	 * Un quilombo.
	 * La hago static para que dure durante el programa.
	 */
	static SDL2pp::SDLTTF ttf;
	GameviewConfigurationsLoader &configs = GameviewConfigurationsLoader::getInstance();
	std::map<int, std::unique_ptr<RenderableObject>> objects;
	Gameview view(objects);
	TextureLoader &textureLoader = TextureLoader::getInstance();
	textureLoader.load(view.getRenderer(), configs.getSpritesToLoad());
	textureLoader.loadMusic(configs.getMusicToLoad());
	textureLoader.loadSFX(configs.getChunksToLoad());
	textureLoader.loadFonts(configs.getFontsToLoad());
	std::unique_ptr<Scene> scene(new Scene());
	view.setScene(scene);

	Socket socket = lobby.move_socket(); 
	Client client(std::move(socket));
	bool running = true;
	bool end_game = false;
	GameDTO gameState;
	ObjectCreator creator;
	while (running && !gameState.is_end_game()) {
		auto t_start = std::chrono::high_resolution_clock::now();
		std::optional<GameDTO> game_optional = client.get_game();
		if (game_optional.has_value()){
			gameState = game_optional.value();
		}
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
		view.render();
		running = handleEvents(&client, view);

		auto t_end = std::chrono::high_resolution_clock::now();
		std::chrono::duration<double> duration = t_end - t_start;
		double seconds = duration.count();
		double rest = rate - seconds;
		if(rest < 0) {
			double behind = -rest;
        	double lost = behind - std::fmod(behind, rate);
        	t_start += std::chrono::duration_cast<std::chrono::high_resolution_clock::duration>(std::chrono::duration<double>(lost));
		}
		else {
			std::this_thread::sleep_for(std::chrono::duration<double>(rest));
		}
	}
	client.join();
	return 0;
}

static bool handleEvents(Client* client, Gameview &view)
{
	SDL_Event event;
	while (SDL_PollEvent(&event) != 0) {
		switch (event.type) {
		case SDL_KEYDOWN: {
			SDL_KeyboardEvent &keyEvent = event.key;
			switch (keyEvent.keysym.sym) {
				case SDLK_LEFT: {
					if (keyEvent.repeat == 0) {
						client->move(LEFT);
					}
					break;
				}
				case SDLK_RIGHT: {
					if (keyEvent.repeat == 0) {
						client->move(RIGHT);
					}
					break;
				}
				case SDLK_UP: {
					if (keyEvent.repeat == 0) {
						client->move(UP);
					}
					break;
				}
				case SDLK_DOWN: {
					if (keyEvent.repeat == 0) {
						client->move(DOWN);
					}
					break;
				}
				case SDLK_r: {
					if (keyEvent.repeat == 0) {
						client->reload();
					}
					break;
				}
				case SDLK_s: {
					if (keyEvent.repeat == 0) {
						client->shoot();
					}
					break;
				}
				case SDLK_e: {
					if (keyEvent.repeat == 0) {
						client->revive_soldier();
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
					client->move(STOP_MOVE);
					break;
				}
				case SDLK_RIGHT: {
					client->move(STOP_MOVE);
					break;
				}
				case SDLK_UP: {
					client->move(STOP_MOVE);
					break;
				}
				case SDLK_DOWN: {
					client->move(STOP_MOVE);
					break;
				}
				case SDLK_s: {
					client->move(STOP_MOVE);
					break;
				}
				case SDLK_PLUS: {
					view.increaseVolume();
					break;
				}
				case SDLK_MINUS: {
					view.lowerVolume();
					break;
				}
				case SDLK_p: {
					view.pauseMusic();
					break;
				}
				case SDLK_o: {
					view.resumeMusic();
					break;
				}
				case SDLK_q: {
					int8_t delta = 10;
					client->throw_explosive_grenade(delta);
					break;
				}
				case SDLK_w: {
					int8_t delta = 10;
					client->throw_smoke_grenade(delta);
					break;
				}
			}
		} // Fin KEY_UP
		break;
		case SDL_QUIT:
			std::cout << "Quit :(" << std::endl;
			return false;
		} // fin switch(event)
	}	  // fin while(SDL_PollEvents)
	return true;
}