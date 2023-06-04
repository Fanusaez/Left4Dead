#include "Player.h"
#include "../common/game_object_state.h"
#include <stdexcept>

Player::Player(SDL2pp::Texture &texture, int id, int initialX, int initialY) :
	RenderableObject(id, initialX, initialY),
	an(texture),
	facingLeft(false),
	moving(false) {}

Player::~Player() = default;

bool Player::isMoving() const {
	//return (this->speed.first != 0 or this->speed.second != 0);
	return this->moving;
}

void Player::updateState(const SoldierObjectDTO &soldierDTO)
{
	if (soldierDTO.id != this->getID())
		throw std::invalid_argument("Invalid ID");

	this->setPositionX(soldierDTO.position_x);
	this->setPositionY(soldierDTO.position_y);
	if (soldierDTO.state == MOVING)
		this->moving = true;
	else
		this->moving = false;

	facingLeft = soldierDTO.facingLeft;
}

void Player::updateState(const ZombieObjectDTO &zombieDTO) {}

/**
 * Notar que el manejo de eventos y la actualización de modelo ocurren en momentos distintos.
 * Esto les va a resultar muy util. 
 */
void Player::update(unsigned dt) {
	if (isMoving()) {
		this->an.update(dt);
	}
}

void Player::render(SDL2pp::Renderer &renderer, SDL2pp::Rect &dst) {
	SDL_RendererFlip flip = this->facingLeft ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE;
	an.render(renderer, dst, flip);
}
