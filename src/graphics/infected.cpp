#include "infected.h"
#include <stdexcept>

Infected::Infected(int id, int initialX, int initialY) :
	RenderableObject(id, initialX, initialY),
	textureLoader(TextureLoader::getInstance()),
	animation(textureLoader.getTexture("Zombie/Walk.png")),
	facingLeft(false),
	state(WALKING)
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

void Infected::changeState(const ZombieObjectState &state)
{
	if (this->state == state)
		return;

	this->state = state;

	if (this->state == WALKING)
		this->animation.changeTexture(this->textureLoader.getTexture("Zombie/Walk.png"));
	else if (this->state == RUNNING)
		this->animation.changeTexture(this->textureLoader.getTexture("Zombie/Run.png"));
	else if (this->state == JUMPING)
		this->animation.changeTexture(this->textureLoader.getTexture("Zombie/Jump.png"));
	else if (this->state == ATTACKING)
		this->animation.changeTexture(this->textureLoader.getTexture("Zombie/Attack_1.png"));
	else
		this->animation.changeTexture(this->textureLoader.getTexture("Zombie/Idle.png"));
}
