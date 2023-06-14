#include "jumper.h"
#include <stdexcept>

Jumper::Jumper(int id, int initialX, int initialY) :
	RenderableObject(id, initialX, initialY),
	textureLoader(TextureLoader::getInstance()),
	animation(textureLoader.getTexture("Jumper/Idle.png")),
	facingLeft(false),
	state(IDLE_ZOMBIE)
{}

Jumper::~Jumper() {}

void Jumper::updateState(const SoldierObjectDTO &soldierDTO) {}

void Jumper::updateState(const ZombieObjectDTO &zombieDTO)
{
	if (zombieDTO.id != this->getID())
		throw std::invalid_argument("Invalid ID");

	this->facingLeft = zombieDTO.facing_left;

	this->setPositionX(zombieDTO.position_x);
	this->setPositionY(zombieDTO.position_y);
	this->changeState(zombieDTO.state);
}

void Jumper::update(unsigned int dt)
{
	this->animation.update(dt);
}

void Jumper::render(SDL2pp::Renderer &renderer, SDL2pp::Rect &dst)
{
	SDL_RendererFlip flip = this->facingLeft ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE;
	this->animation.render(renderer, dst, flip);
}

void Jumper::renderAudio(SDL2pp::Mixer &mixer) {}

void Jumper::changeState(const ZombieObjectState &state)
{
	if (this->state == state)
		return;

	this->state = state;

	if (this->state == WALKING) {
		this->animation.changeTexture(this->textureLoader.getTexture("Jumper/Walk.png"));
	} else if (this->state == RUNNING) {
		this->animation.changeTexture(this->textureLoader.getTexture("Jumper/Run.png"));
	} else if (this->state == JUMPING) {
		this->animation.changeTexture(this->textureLoader.getTexture("Jumper/Jump.png"));
	} else if (this->state == ATTACKING) {
		this->animation.changeTexture(this->textureLoader.getTexture("Jumper/Attack_1.png"));
	} else if (this->state == BEING_ATTACKED) {
		this->animation.changeTexture(this->textureLoader.getTexture("Jumper/Hurt.png"));
	} else if (this->state == DEAD) {
		this->animation.changeTexture(this->textureLoader.getTexture("Jumper/Dead.png"));
		this->animation.noLoop();
	} else {
		this->animation.changeTexture(this->textureLoader.getTexture("Jumper/Idle.png"));
		this->animation.noLoop();
	}
}
