#include "Player.h"
#include <stdexcept>

Player::Player(int id, int initialX, int initialY) :
	RenderableObject(id, initialX, initialY),
	textureLoader(TextureLoader::getInstance()),
	an(textureLoader.getTexture("Soldier_1/Idle.png")),
	facingLeft(false),
	state(IDLE_SOLDIER),
	playSFX(false)
{}

Player::~Player() = default;

bool Player::isMoving() const
{
	return this->state == MOVING;
}

void Player::updateState(const SoldierObjectDTO &soldierDTO)
{
	if (soldierDTO.id != this->getID())
		throw std::invalid_argument("Invalid ID");

	this->facingLeft = soldierDTO.facing_left;
	this->setPositionX(soldierDTO.position_x);
	this->setPositionY(soldierDTO.position_y);
	this->changeState(soldierDTO.state);
}

void Player::updateState(const ZombieObjectDTO &zombieDTO) {}

/**
 * Notar que el manejo de eventos y la actualización de modelo ocurren en momentos distintos.
 * Esto les va a resultar muy util. 
 */
void Player::update(unsigned dt)
{
	if (this->state != IDLE_SOLDIER)
		this->an.update(dt);
}

void Player::render(SDL2pp::Renderer &renderer, SDL2pp::Rect &dst)
{
	SDL_RendererFlip flip = this->facingLeft ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE;
	an.render(renderer, dst, flip);
}

void Player::renderAudio(SDL2pp::Mixer &mixer)
{
	if (not this->sfx or not this->playSFX)
		return;
	mixer.PlayChannel(-1, *(this->sfx), this->sfxLoops);
	this->playSFX = false;
}

void Player::changeState(const SoldierObjectState &state)
{
	if (this->state == state)
		return;

	this->state = state;

	if (this->state == SHOOTING) {
		this->an.changeTexture(this->textureLoader.getTexture("Soldier_1/Shot_1.png"));
		this->sfx = nullptr;
	} else if (this->state == RELOADING) {
		this->an.changeTexture(this->textureLoader.getTexture("Soldier_1/Recharge.png"));
		this->an.noLoop();
		this->sfx = nullptr;
	} else if (this->state == MOVING) {
		this->an.changeTexture(this->textureLoader.getTexture("Soldier_1/Walk.png"));
		this->sfx = nullptr;
	} else if (this->state == SOLDIER_DEAD) {
		this->an.changeTexture(this->textureLoader.getTexture("Soldier_1/Dead.png"));
		this->an.noLoop();
		this->sfx = this->textureLoader.getChunk("Soldier_1/Death.mp3");
		this->sfxLoops = 0;
		this->playSFX = true;
	} else if (this->state == SOLDIER_HURT) {
		this->an.changeTexture(this->textureLoader.getTexture("Soldier_1/Hurt.png"));
		this->sfx = nullptr;
	} else {
		this->an.changeTexture(this->textureLoader.getTexture("Soldier_1/Idle.png"));
		this->an.noLoop();
		this->sfx = nullptr;
	}
}
