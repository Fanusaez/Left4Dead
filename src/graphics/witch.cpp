#include "witch.h"
#include <stdexcept>

Witch::Witch(int id, int initialX, int initialY) :
	RenderableObject(id, initialX, initialY),
	textureLoader(TextureLoader::getInstance()),
	animation(textureLoader.getTexture("Witch/Idle.png")),
	facingLeft(false),
	state(IDLE_ZOMBIE)
{}

Witch::~Witch() {}

void Witch::updateState(const SoldierObjectDTO &soldierDTO) {}

void Witch::updateState(const ZombieObjectDTO &zombieDTO)
{
	if (zombieDTO.id != this->getID())
		throw std::invalid_argument("Invalid ID");

	this->facingLeft = zombieDTO.facing_left;

	this->setPositionX(zombieDTO.position_x);
	this->setPositionY(zombieDTO.position_y);
	this->changeState(zombieDTO.state);
}

void Witch::update(unsigned int dt)
{
	this->animation.update(dt);
}

void Witch::render(SDL2pp::Renderer &renderer, SDL2pp::Rect &dst)
{
	SDL_RendererFlip flip = this->facingLeft ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE;
	this->animation.render(renderer, dst, flip);
}

void Witch::renderAudio(SDL2pp::Mixer &mixer) {}

void Witch::changeState(const ZombieObjectState &state)
{
	if (this->state == state)
		return;

	this->state = state;

	if (this->state == WALKING) {
		this->animation.changeTexture(this->textureLoader.getTexture("Witch/Walk.png"));
	} else if (this->state == RUNNING) {
		this->animation.changeTexture(this->textureLoader.getTexture("Witch/Run.png"));
	} else if (this->state == JUMPING) {
		this->animation.changeTexture(this->textureLoader.getTexture("Witch/Jump.png"));
	} else if (this->state == ATTACKING) {
		this->animation.changeTexture(this->textureLoader.getTexture("Witch/Attack_1.png"));
	} else if (this->state == BEING_ATTACKED) {
		this->animation.changeTexture(this->textureLoader.getTexture("Witch/Hurt.png"));
	} else if (this->state == DEAD) {
		this->animation.changeTexture(this->textureLoader.getTexture("Witch/Dead.png"));
		this->animation.noLoop();
	} else if (this->state == SCREAMING) {
		this->animation.changeTexture(this->textureLoader.getTexture("Witch/Scream.png"));
	} else {
		this->animation.changeTexture(this->textureLoader.getTexture("Zombie/Idle.png"));
		this->animation.noLoop();
	}
}
