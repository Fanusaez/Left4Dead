#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2pp/SDL2pp.hh>
#include "Player.h"
#include <iostream>
#include <exception>
#include <unistd.h>
#include <string>

static const std::string AssetsPath = ASSETS_PATH;

static bool handleEvents(Player &player);
static void render(SDL2pp::Renderer &renderer, Player &player);
static void update(Player &player, float dt);

int main(int argc, char *argv[])
{
	try {
		SDL2pp::SDL sdl(SDL_INIT_VIDEO);
		SDL2pp::SDLImage image(IMG_INIT_PNG);
		SDL2pp::Window window("Game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
				      1280, 720,
				      SDL_WINDOW_RESIZABLE);
		SDL2pp::Renderer renderer(window, -1, SDL_RENDERER_ACCELERATED);
		SDL2pp::Texture im(renderer, SDL2pp::Surface(std::string(AssetsPath).append("Soldier_1/Walk.png")).SetColorKey(true, 0));
		Player player(im);

		bool running = true;

		while (running) {
			running = handleEvents(player);
			update(player, FRAME_RATE);
			render(renderer, player);
			// la cantidad de segundos que debo dormir se debe ajustar en función
			// de la cantidad de tiempo que demoró el handleEvents y el render
			usleep(FRAME_RATE);
		}
	} catch (std::exception &e) {
		std::cout << e.what() << std::endl;
		return 1;
	}
	return 0;
}

static bool handleEvents(Player &player) {
	SDL_Event event;
	// Para el alumno: Buscar diferencia entre waitEvent y pollEvent
	while(SDL_PollEvent(&event)){
		switch(event.type) {
			case SDL_KEYDOWN: {
				// ¿Qué pasa si mantengo presionada la tecla?
				SDL_KeyboardEvent& keyEvent = (SDL_KeyboardEvent&) event;
				switch (keyEvent.keysym.sym) {
					case SDLK_LEFT:
						player.moveLeft();
						break;
					case SDLK_RIGHT:
						player.moveRigth();
						break;
				}
			} // Fin KEY_DOWN
				break;
			case SDL_KEYUP: {
				SDL_KeyboardEvent& keyEvent = (SDL_KeyboardEvent&) event;
				switch (keyEvent.keysym.sym) {
					case SDLK_LEFT:
						player.stopMoving();
						break;
					case SDLK_RIGHT:
						player.stopMoving();
						break;
				}
			}// Fin KEY_UP
				break;
			case SDL_QUIT:
				std::cout << "Quit :(" << std::endl;
				return false;
		} // fin switch(event)
	} // fin while(SDL_PollEvents)
	return true;
}

static void render(SDL2pp::Renderer &renderer, Player &player) {
	// TODO: fix this. I'm loading the backgorund everytime xd.
	SDL2pp::Texture background(renderer, SDL2pp::Surface(std::string(AssetsPath).append("backgrounds/War1/Pale/War.png")).SetColorKey(true, 0));
	renderer.Clear();
	renderer.Copy(background);
	player.render(renderer);
	renderer.Present();
}

static void update(Player &player, float dt) {
	player.update(dt);
}
