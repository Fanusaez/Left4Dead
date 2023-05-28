#include "Player.h"

Player::Player(SDL2pp::Texture &texture, int id, int initialX, int initialY) :
	RenderableObject(id, initialX, initialY),
	an(texture),
	facingLeft(false),
	speed(0, 0),
	moving(false) {}

Player::~Player() = default;

bool Player::isMoving() const {
	//return (this->speed.first != 0 or this->speed.second != 0);
	return this->moving;
}

/**
 * Notar que el manejo de eventos y la actualización de modelo ocurren en momentos distintos.
 * Esto les va a resultar muy util. 
 */
void Player::update(unsigned dt) {
	if (isMoving()) {
		this->an.update(dt);
		this->xPosition += this->speed.first;
		this->yPosition += this->speed.second;
	}
}

void Player::render(SDL2pp::Renderer &renderer, SDL2pp::Rect &dst) {
	SDL_RendererFlip flip = this->facingLeft ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE;
	an.render(renderer, dst, flip);
}

void Player::moveRigth() {
	this->speed.first = 5;
	this->speed.second = 0;
	this->facingLeft = false;
	this->moving = true;
}

void Player::moveLeft() {
	this->speed.first = -5;
	this->speed.second = 0;
	this->facingLeft = true;
	this->moving = true;
}

void Player::moveUp() {
	this->speed.first = 0;
	this->speed.second = -3;
	this->moving = true;
}

void Player::moveDown() {
	this->speed.first = 0;
	this->speed.second = 3;
	this->moving = true;
}

void Player::stopMoving() {
	this->speed.first = 0;
	this->speed.second = 0;
	this->moving = false;
}
