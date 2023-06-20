#include "grenade.h"
#include <stdexcept>

Grenade::Grenade(int id, int initialX, int initialY) :
	RenderableObject(id, initialX, initialY),
	textureLoader(TextureLoader::getInstance()),
	animation(textureLoader.getTexture("Soldier_1/Explosion.png")),
	playSFX(false),
	lastChannel(-1),
	exploting(true)
{
	this->animation.noLoop();
	this->sfx = this->textureLoader.getChunk("Soldier_1/Explosion.mp3");
	this->playSFX = true;
}

Grenade::~Grenade() {}

void Grenade::updateState(const SoldierObjectDTO &soldierDTO) {}

void Grenade::updateState(const ZombieObjectDTO &zombieDTO) {}

void Grenade::updateState(const GrenadeObjectDTO &grenadeDTO)
{
	if (grenadeDTO.id != this->getID())
		throw std::invalid_argument("Invalid ID");

	this->setPositionX(grenadeDTO.position_x);
	this->setPositionY(grenadeDTO.position_y);
	this->exploting = grenadeDTO.exploting;
}

void Grenade::update(unsigned int dt)
{
	this->animation.update(dt);
}

void Grenade::render(SDL2pp::Renderer &renderer, SDL2pp::Rect &dst)
{
	if (this->exploting) {
		SDL_RendererFlip flip = SDL_FLIP_NONE;
		this->animation.render(renderer, dst, flip);
	}
}

void Grenade::renderAudio(SDL2pp::Mixer &mixer)
{
	if (not this->playSFX or not this->exploting)
		return;

	if (this->lastChannel != -1) // This object is playing something
		mixer.HaltChannel(this->lastChannel); // Stop playing

	if (this->sfx)
		this->lastChannel = mixer.PlayChannel(-1, *(this->sfx), 0);
	else
		this->lastChannel = -1;

	this->playSFX = false;
}
