#include <iostream>
#include "client.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2pp/SDL2pp.hh>
#include "gameview.h"
#include "Player.h"
#include "texture_loader.h"
#include "gameview_configs_loader.h"
#include "scene.h"
#include <iostream>
#include <exception>
#include <unistd.h>
#include <string>
#include <list>
#include <map>
#include <memory>
#include <optional>

static bool handleEvents(Client* client);

int main(int argc, char *argv[])
{
	Client client(argv[1], argv[2]);
	if (std::string(argv[3]) == "c"){
		std::string map = "map1";
		client.create_scenario(map);
		std::cout << "Creo el escenario" << std::endl;
	} else {
		int32_t code = 0;
		client.join_scenario(code);
		std::cout << "Joineo escenario" << std::endl;
	}

	GameviewConfigurationsLoader &configs = GameviewConfigurationsLoader::getInstance();
	std::map<int, std::unique_ptr<RenderableObject>> objects;
	Gameview view(objects);
	TextureLoader &textureLoader = TextureLoader::getInstance();
	textureLoader.load(view.getRenderer(), configs.getSpritesToLoad());
	std::unique_ptr<Scene> scene(new Scene(
			textureLoader.getTexture("backgrounds/War1/Pale/Full_Sky.png"),
			textureLoader.getTexture("backgrounds/War1/Pale/Far_Background.png"),
			textureLoader.getTexture("backgrounds/War1/Pale/Floor.png"))
			);
	view.setScene(scene);

	bool running = true;

	GameDTO gameState;
	while (running) {
		std::optional<GameDTO> game_optional = client.get_game();
		if (game_optional.has_value()){
			gameState = game_optional.value();
		}
		std::vector<SoldierObjectDTO> soldiers = gameState.get_soldiers();
		if (soldiers.size() == 0) {
			std::cerr << "Error\n";
			client.join();
			return 1;
		}
		for (auto& soldier: soldiers){
			if(objects.find(soldier.id) == objects.end()){
				std::unique_ptr<RenderableObject> ptr1(new Player(textureLoader.getTexture("Soldier_1/Walk.png"), soldier.id, soldier.position_x, soldier.position_y));
				objects[ptr1->getID()] = std::move(ptr1);
				view.assignMainObject(1);
			}
			else {
				RenderableObject& ptr1 = *(objects.at(soldier.id));
				ptr1.setPositionX(soldier.position_x);
				ptr1.setPositionY(soldier.position_y);
			}
		}
		for (auto &object : objects)
			object.second->update(configs.FRAME_RATE);
		view.render();
		running = handleEvents(&client);
		usleep(configs.FRAME_RATE);
	}
	client.join();
	return 0;
}

static bool handleEvents(Client* client)
{
	SDL_Event event;
	// Para el alumno: Buscar diferencia entre waitEvent y pollEvent
	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_KEYDOWN:
		{
			// ¿Qué pasa si mantengo presionada la tecla?
			SDL_KeyboardEvent &keyEvent = (SDL_KeyboardEvent &)event;
			switch (keyEvent.keysym.sym)
			{
			case SDLK_LEFT:
				client->move(LEFT);
				break;
			case SDLK_RIGHT:
				client->move(RIGHT);
				break;
			case SDLK_UP:
				client->move(UP);
				break;
			case SDLK_DOWN:
				client->move(DOWN);
				break;
			}
		} // Fin KEY_DOWN
		break;
		case SDL_KEYUP:
		{
			SDL_KeyboardEvent &keyEvent = (SDL_KeyboardEvent &)event;
			switch (keyEvent.keysym.sym)
			{
			case SDLK_LEFT:
				
				break;
			case SDLK_RIGHT:
				
				break;
			case SDLK_UP:
				
				break;
			case SDLK_DOWN:
				
				break;
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
