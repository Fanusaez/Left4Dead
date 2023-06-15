#include "infected.h"
#include <stdexcept>

Infected::Infected(int id, int initialX, int initialY) :
	RenderableObject(id, initialX, initialY),
	textureLoader(TextureLoader::getInstance()),
	animation(textureLoader.getTexture("Zombie/Idle.png")),
	facingLeft(false),
	state(IDLE_ZOMBIE),
	playSFX(false)
{}

Infected::~Infected() {}

void Infected::updateState(const SoldierObjectDTO &soldierDTO) {}

void Infected::updateState(const ZombieObjectDTO &zombieDTO)
{
	if (zombieDTO.id != this->getID())
		throw std::invalid_argument("Invalid ID");

	this->facingLeft = zombieDTO.facing_left; 

	this->setPositionX(zombieDTO.position_x);
	this->setPositionY(zombieDTO.position_y);
	this->changeState(zombieDTO.state);
}

void Infected::update(unsigned int dt)
{
	this->animation.update(dt);
}

void Infected::render(SDL2pp::Renderer &renderer, SDL2pp::Rect &dst)
{
	SDL_RendererFlip flip = this->facingLeft ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE;
	this->animation.render(renderer, dst, flip);
}

void Infected::renderAudio(SDL2pp::Mixer &mixer)
{
	if (not this->sfx or not this->playSFX)
		return;
	mixer.PlayChannel(-1, *(this->sfx), this->sfxLoops);
	this->playSFX = false;
}

void Infected::changeState(const ZombieObjectState &state)
{
	if (this->state == state)
		return;

	this->state = state;

	if (this->state == WALKING) {
		this->animation.changeTexture(this->textureLoader.getTexture("Zombie/Walk.png"));
	} else if (this->state == RUNNING) {
		this->animation.changeTexture(this->textureLoader.getTexture("Zombie/Run.png"));
	} else if (this->state == JUMPING) {
		this->animation.changeTexture(this->textureLoader.getTexture("Zombie/Jump.png"));
	} else if (this->state == ATTACKING) {
		this->animation.changeTexture(this->textureLoader.getTexture("Zombie/Attack_1.png"));
	} else if (this->state == BEING_ATTACKED) {
		this->animation.changeTexture(this->textureLoader.getTexture("Zombie/Hurt.png"));
		this->sfx = this->textureLoader.getChunk("Zombie/Hurt.mp3");
		this->sfxLoops = 0;
		this->playSFX = true;
	} else if (this->state == DEAD) {
		this->animation.changeTexture(this->textureLoader.getTexture("Zombie/Dead.png"));
		this->animation.noLoop();
		this->sfx = this->textureLoader.getChunk("Zombie/Dead.mp3");
		this->sfxLoops = 0;
		this->playSFX = true;
	} else {
		this->animation.changeTexture(this->textureLoader.getTexture("Zombie/Idle.png"));
		this->animation.noLoop();
	}
}
