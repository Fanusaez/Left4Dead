#include "Player.h"

Player::Player(SDL2pp::Texture &texture):
	an(texture),
	facingLeft(false),
	position(910, 900),
	speed(0, 0){}

Player::~Player() {}

bool Player::isMoving() const
{
	return (this->speed.first != 0 or this->speed.second != 0);
}

/**
 * Notar que el manejo de eventos y la actualización de modelo ocurren en momentos distintos.
 * Esto les va a resultar muy util. 
 */
void Player::update(float dt) {
	if (isMoving()) {
		this->an.update(dt);
		this->position.first += this->speed.first;
		this->position.second += this->speed.second;
	}
}

void Player::render(SDL2pp::Renderer &renderer) {
    SDL_RendererFlip flip = this->facingLeft ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE;
    an.render(renderer, SDL2pp::Rect(this->position.first, this->position.second, 150, 150), flip);
}

void Player::moveRigth() {
	this->speed.first = 3;
	this->speed.second = 0;
	this->facingLeft = false;
}

void Player::moveLeft() {
	this->speed.first = -3;
	this->speed.second = 0;
	this->facingLeft = true;
}

void Player::moveUp()
{
	this->speed.first = 0;
	this->speed.second = -3;
}

void Player::moveDown()
{
	this->speed.first = 0;
	this->speed.second = 3;
}

void Player::stopMoving() {
	this->speed.first = 0;
	this->speed.second = 0;
}
