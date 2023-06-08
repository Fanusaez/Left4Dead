#include "Player.h"
#include <stdexcept>

Player::Player(int id, int initialX, int initialY) :
	RenderableObject(id, initialX, initialY),
	textureLoader(TextureLoader::getInstance()),
	an(textureLoader.getTexture("Soldier_1/Idle.png")),
	facingLeft(false),
	state(IDLE_SOLDIER)
{}

Player::~Player() = default;

bool Player::isMoving() const {
	return this->state == MOVING;
}

void Player::updateState(const SoldierObjectDTO &soldierDTO)
{
	if (soldierDTO.id != this->getID())
		throw std::invalid_argument("Invalid ID");

	this->facingLeft = soldierDTO.facing_left;
	this->setPositionX(soldierDTO.position_x);
	this->setPositionY(soldierDTO.position_y);
	//std::cout<<xPosition<<","<<yPosition<<std::endl;
	this->changeState(soldierDTO.state);
}

void Player::updateState(const ZombieObjectDTO &zombieDTO) {}

/**
 * Notar que el manejo de eventos y la actualización de modelo ocurren en momentos distintos.
 * Esto les va a resultar muy util. 
 */
void Player::update(unsigned dt) {
	if (this->state != IDLE_SOLDIER)
		this->an.update(dt);
}

void Player::render(SDL2pp::Renderer &renderer, SDL2pp::Rect &dst) {
	SDL_RendererFlip flip = this->facingLeft ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE;
	an.render(renderer, dst, flip);
}

void Player::changeState(const SoldierObjectState &state)
{
	if (this->state == state)
		return;

	this->state = state;

	if (this->state == SHOOTING)
		this->an.changeTexture(this->textureLoader.getTexture("Soldier_1/Shot_1.png"));
	else if (this->state == RELOADING)
		this->an.changeTexture(this->textureLoader.getTexture("Soldier_1/Recharge.png"));
	else if (this->state == MOVING)
		this->an.changeTexture(this->textureLoader.getTexture("Soldier_1/Walk.png"));
	else
		this->an.changeTexture(this->textureLoader.getTexture("Soldier_1/Idle.png"));
}
