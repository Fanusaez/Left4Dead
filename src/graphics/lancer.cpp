#include "lancer.h"
#include <stdexcept>

Lancer::Lancer(int id, int initialX, int initialY) :
	RenderableObject(id, initialX, initialY),
	textureLoader(TextureLoader::getInstance()),
	animation(textureLoader.getTexture("Spear/Idle.png")),
	facingLeft(false),
	state(IDLE_ZOMBIE),
	playSFX(false),
	lastChannel(-1)
{}

Lancer::~Lancer() {}

void Lancer::updateState(const SoldierObjectDTO &soldierDTO) {}

void Lancer::updateState(const ZombieObjectDTO &zombieDTO)
{
	if (zombieDTO.id != this->getID())
		throw std::invalid_argument("Invalid ID");

	this->facingLeft = zombieDTO.facing_left;

	this->setPositionX(zombieDTO.position_x);
	this->setPositionY(zombieDTO.position_y);
	this->changeState(zombieDTO.state);
}

void Lancer::updateState(const GrenadeObjectDTO &grenadeDTO) {}

void Lancer::update(unsigned int dt)
{
	this->animation.update(dt);
}

void Lancer::render(SDL2pp::Renderer &renderer, SDL2pp::Rect &dst)
{
	SDL_RendererFlip flip = this->facingLeft ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE;
	this->animation.render(renderer, dst, flip);
}

void Lancer::renderAudio(SDL2pp::Mixer &mixer)
{
	if (not this->playSFX)
		return;

	if (this->lastChannel != -1) // This object is playing something
		mixer.HaltChannel(this->lastChannel); // Stop playing

	if (this->sfx)
		this->lastChannel = mixer.PlayChannel(-1, *(this->sfx), this->sfxLoops);
	else
		this->lastChannel = -1;

	this->playSFX = false;
}

void Lancer::changeState(const ZombieObjectState &state)
{
	if (this->state == state)
		return;

	this->state = state;

	if (this->state == WALKING) {
		this->animation.changeTexture(this->textureLoader.getTexture("Spear/Walk.png"));
		this->sfx = nullptr;
	} else if (this->state == RUNNING) {
		this->animation.changeTexture(this->textureLoader.getTexture("Spear/Run.png"));
		this->sfx = nullptr;
	} else if (this->state == ATTACKING) {
		this->animation.changeTexture(this->textureLoader.getTexture("Spear/Attack_1.png"));
		this->sfx = nullptr;
	} else if (this->state == BEING_ATTACKED) {
		this->animation.changeTexture(this->textureLoader.getTexture("Spear/Hurt.png"));
		this->sfx = this->textureLoader.getChunk("Zombie/Hurt.mp3");
		this->sfxLoops = 0;
	} else if (this->state == DEAD) {
		this->animation.changeTexture(this->textureLoader.getTexture("Spear/Dead.png"));
		this->animation.noLoop();
		this->sfx = this->textureLoader.getChunk("Zombie/Dead.mp3");
		this->sfxLoops = 0;
	} else {
		this->animation.changeTexture(this->textureLoader.getTexture("Spear/Idle.png"));
		this->animation.noLoop();
		this->sfx = nullptr;
	}
	this->playSFX = true;
}
