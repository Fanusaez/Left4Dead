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

static const std::string TmpAssetsPath = ASSETS_PATH;

static bool handleEvents(Player &player);

int main(int argc, char *argv[])
{
	try
	{
		GameviewConfigurationsLoader &configs = GameviewConfigurationsLoader::getInstance();
		std::map<int, std::unique_ptr<RenderableObject>> objects;
		Gameview view(objects);
		TextureLoader &textureLoader = TextureLoader::getInstance();
		textureLoader.load(view.getRenderer(), configs.getSpritesToLoad());
		std::unique_ptr<RenderableObject> ptr1(new Player(textureLoader.getTexture("Soldier_1/Walk.png"), 1, 1000, 900));
		std::unique_ptr<RenderableObject> ptr2(new Player(textureLoader.getTexture("Soldier_1/Walk.png"), 2, 700, 900));
		objects[ptr1->getID()] = std::move(ptr1);
		objects[ptr2->getID()] = std::move(ptr2);
		view.assignMainObject(1);
		std::unique_ptr<Scene> scene(new Scene(
			textureLoader.getTexture("backgrounds/War1/Pale/Full_Sky.png"),
			textureLoader.getTexture("backgrounds/War1/Pale/Far_Background.png"),
			textureLoader.getTexture("backgrounds/War1/Pale/Floor.png"))
			);
		view.setScene(scene);
		//SDL2pp::Music music(std::string(TmpAssetsPath).append("Music/10. no way back.flac"));

		bool running = true;

		while (running)
		{
			Player &player = static_cast<Player &>(*(objects.at(1)));
			running = handleEvents(player);
			player.update(configs.FRAME_RATE);
			//update
			view.render();
			// la cantidad de segundos que debo dormir se debe ajustar en función
			// de la cantidad de tiempo que demoró el handleEvents y el render
			usleep(configs.FRAME_RATE);
		}
	}
	catch (std::exception &e)
	{
		std::cout << e.what() << std::endl;
		return 1;
	}
	return 0;
}

static bool handleEvents(Player &player)
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
				player.moveLeft();
				break;
			case SDLK_RIGHT:
				player.moveRigth();
				break;
			case SDLK_UP:
				player.moveUp();
				break;
			case SDLK_DOWN:
				player.moveDown();
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
				player.stopMoving();
				break;
			case SDLK_RIGHT:
				player.stopMoving();
				break;
			case SDLK_UP:
				player.stopMoving();
				break;
			case SDLK_DOWN:
				player.stopMoving();
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
