#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2pp/SDL2pp.hh>
#include "Player.h"
#include "texture_loader.h"
#include "stage.h"
#include <iostream>
#include <exception>
#include <unistd.h>
#include <string>
#include <list>

static bool handleEvents(Player &player, Stage &stage);

int main(int argc, char *argv[])
{
	try
	{
		SDL2pp::SDL sdl(SDL_INIT_VIDEO);
		SDL2pp::SDLImage image(IMG_INIT_PNG);
		SDL2pp::Window window("Game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
							  1280, 720,
							  SDL_WINDOW_RESIZABLE);
		SDL2pp::Renderer renderer(window, -1, SDL_RENDERER_ACCELERATED);
		renderer.SetLogicalSize(1920, 1080);
		std::list<std::string> spritesToLoad;
		spritesToLoad.push_back("Soldier_1/Walk.png");
		spritesToLoad.push_back("backgrounds/War1/Pale/Full_Sky.png");
		spritesToLoad.push_back("backgrounds/War1/Pale/Far_Background.png");
		spritesToLoad.push_back("backgrounds/War1/Pale/Floor.png");
		TextureLoader textureLoader;
		textureLoader.load(renderer, spritesToLoad);
		Player player(textureLoader.getTexture("Soldier_1/Walk.png"));
		Stage stage(
			textureLoader.getTexture("backgrounds/War1/Pale/Full_Sky.png"),
			textureLoader.getTexture("backgrounds/War1/Pale/Far_Background.png"),
			textureLoader.getTexture("backgrounds/War1/Pale/Floor.png"));

		bool running = true;

		while (running)
		{
			running = handleEvents(player, stage);
			stage.update(FRAME_RATE);
			player.update(FRAME_RATE);
			renderer.Clear();
			stage.render(renderer);
			player.render(renderer);
			renderer.Present();
			// la cantidad de segundos que debo dormir se debe ajustar en función
			// de la cantidad de tiempo que demoró el handleEvents y el render
			usleep(FRAME_RATE);
		}
	}
	catch (std::exception &e)
	{
		std::cout << e.what() << std::endl;
		return 1;
	}
	return 0;
}

static bool handleEvents(Player &player, Stage &stage)
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
				stage.moveRight();
				break;
			case SDLK_RIGHT:
				player.moveRigth();
				stage.moveLeft();
				break;
			case SDLK_UP:
				player.moveUp();
				stage.stop();
				break;
			case SDLK_DOWN:
				player.moveDown();
				stage.stop();
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
				stage.stop();
				break;
			case SDLK_RIGHT:
				player.stopMoving();
				stage.stop();
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

static void update(Player &player, float dt)
{
	player.update(dt);
}