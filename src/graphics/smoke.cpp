#include "smoke.h"
#include <stdexcept>

Smoke::Smoke(int id, int initialX, int initialY) :
	RenderableObject(id, initialX, initialY),
	textureLoader(TextureLoader::getInstance()),
	animation(textureLoader.getTexture("Soldier_3/Smoke.png")),
	playSFX(false),
	lastChannel(-1)
{
	this->animation.noLoop();
	this->sfx = this->textureLoader.getChunk("Soldier_3/Smoke.mp3");
	this->playSFX = true;
}

Smoke::~Smoke() {}

void Smoke::updateState(const SoldierObjectDTO &soldierDTO)
{}

void Smoke::updateState(const ZombieObjectDTO &zombieDTO)
{}

void Smoke::updateState(const GrenadeObjectDTO &grenadeDTO)
{
	if (grenadeDTO.id != this->getID())
		throw std::invalid_argument("Invalid ID");

	this->setPositionX(grenadeDTO.position_x);
	this->setPositionY(grenadeDTO.position_y);
}

void Smoke::update(unsigned int dt)
{
	this->animation.update(dt);
}

void Smoke::render(SDL2pp::Renderer &renderer, SDL2pp::Rect &dst)
{
	SDL_RendererFlip flip = SDL_FLIP_NONE;
	this->animation.render(renderer, dst, flip);
}

void Smoke::renderAudio(SDL2pp::Mixer &mixer)
{
	if (not this->playSFX)
		return;

	if (this->lastChannel != -1) // This object is playing something
		mixer.HaltChannel(this->lastChannel); // Stop playing

	if (this->sfx)
		this->lastChannel = mixer.PlayChannel(-1, *(this->sfx), 0);
	else
		this->lastChannel = -1;

	this->playSFX = false;
}
