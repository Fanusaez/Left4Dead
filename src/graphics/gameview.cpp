#include "gameview.h"
#include <cstdlib>
#include <utility>
// TODO: sacar esto
#include "Player.h"

#define CHUNK_SIZE 4096

Gameview::Gameview(std::map<int, std::unique_ptr<RenderableObject>> &gameObjects) :
	sdl(SDL_INIT_VIDEO | SDL_INIT_AUDIO),
	ttf(),
	window("Game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
	       1280, 720,
	       SDL_WINDOW_RESIZABLE),
	renderer(window, -1, SDL_RENDERER_ACCELERATED),
	mixer(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, CHUNK_SIZE),
	objects(gameObjects)
{
	this->renderer.SetLogicalSize(1920, 1080);
}

void Gameview::assignMainObject(int id)
{
	if (this->objects.find(id) == this->objects.end())
		return;

	RenderableObject &mainObject = *(this->objects.at(id));
	this->mainObjectID = id;
	this->previousX = mainObject.getPositionX();

	this->hudFont = TextureLoader::getInstance().getFont("Fonts/Vera.ttf");
}

void Gameview::setScene(std::unique_ptr <Scene> &newScene)
{
	this->scene = std::move(newScene);
	this->scene->playMusic(this->mixer);
}

void Gameview::render()
{
	this->renderer.Clear();
	if (not this->mainObjectID.has_value())
		this->renderFixedCamera();
	else
		this->renderRelativeToMainObject();
}

void Gameview::lowerVolume()
{
	int volume = this->mixer.GetVolume(-1) - 10;
	volume = volume < 0 ? 0 : volume;
	this->mixer.SetVolume(-1, volume);
	this->mixer.SetMusicVolume(volume);
}

void Gameview::increaseVolume()
{
	int volume = this->mixer.GetVolume(-1) + 10;
	volume = volume > MIX_MAX_VOLUME ? MIX_MAX_VOLUME : volume;
	this->mixer.SetVolume(-1, volume);
	this->mixer.SetMusicVolume(volume);
}

void Gameview::pauseMusic()
{
	this->mixer.PauseMusic();
}

void Gameview::resumeMusic()
{
	this->mixer.ResumeMusic();
}

void Gameview::renderRelativeToMainObject()
{
	RenderableObject &mainObject = *(this->objects.at(this->mainObjectID.value()));
	if (mainObject.getPositionX() != this->previousX) {
		int offset = mainObject.getPositionX() - this->previousX;
		this->scene->increaseOffset(offset);
		this->previousX = mainObject.getPositionX();
	}

	this->scene->render(this->renderer);
	SDL2pp::Rect mainObjectDst(885, mainObject.getPositionY(), 150, 150);
	mainObject.render(this->renderer, mainObjectDst);
	mainObject.renderAudio(this->mixer);

	for (auto &obj: this->objects) {
		if (obj.first == mainObject.getID())
			continue;
		RenderableObject &object = *(obj.second);
		int distance = std::abs(mainObject.getPositionX() - object.getPositionX());
		if (distance > 1110)
			continue;
		SDL2pp::Rect objDst(
			885 + object.getPositionX() - mainObject.getPositionX(),
			object.getPositionY(), 150, 150);
		object.render(this->renderer, objDst);
		object.renderAudio(this->mixer);
	}

	// TODO: Arreglar esto. Exorcisar este cast horrible
	int health = static_cast<Player &>(mainObject).getHealth();
	int bullets = static_cast<Player &>(mainObject).getBullets();
	this->renderHud(health, bullets);
	this->renderer.Present();
}

void Gameview::renderFixedCamera()
{
	this->scene->render(this->renderer);
	for (auto &obj: this->objects) {
		RenderableObject &object = *(obj.second);
		SDL2pp::Rect objDst(
			object.getPositionX(),
			object.getPositionY(),
			150, 150);
		object.render(this->renderer, objDst);
		object.renderAudio(this->mixer);
	}
	this->renderer.Present();
}

void Gameview::renderHud(int health, int bullets)
{
	std::string text =
		"Health : "
		+ std::to_string(health)
		+ "     Ammo: "
		+ std::to_string(bullets);

	SDL2pp::Texture textSprite(
		this->renderer,
		this->hudFont->RenderText_Blended(text, SDL_Color{255, 255, 255, 255}));
	this->renderer.Copy(
		textSprite,
		SDL2pp::NullOpt,
		SDL2pp::Rect(0, 0, textSprite.GetWidth(), textSprite.GetHeight()));
}

SDL2pp::Renderer &Gameview::getRenderer()
{
	return this->renderer;
}

Gameview::~Gameview() = default;
