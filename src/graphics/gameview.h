#ifndef GAMEVIEW_H
#define GAMEVIEW_H

#include <SDL2/SDL.h>
#include <SDL2pp/SDL2pp.hh>
#include <memory>
#include <map>
#include <optional>
#include "scene.h"
#include "texture_loader.h"
#include "renderable_object.h"

class Gameview {
	SDL2pp::SDL sdl;

	SDL2pp::Window window;

	SDL2pp::Renderer renderer;

	SDL2pp::Mixer mixer;

	std::unique_ptr <Scene> scene;

	std::optional<int> mainObjectID;

	int previousX;

	std::map<int, std::unique_ptr<RenderableObject>> &objects;

public:
	Gameview(std::map<int, std::unique_ptr<RenderableObject>> &gameObjects);

	void assignMainObject(int id);

	void setScene(std::unique_ptr <Scene> &newScene);

	void render();

	void lowerVolume();

	void increaseVolume();

	void pauseMusic();

	void resumeMusic();

	SDL2pp::Renderer &getRenderer();

	~Gameview();

private:
	//int measureToPixels(int measure) const;

	//void renderAudio();
	void renderRelativeToMainObject();

	void renderFixedCamera();
};

#endif //GAMEVIEW_H
