#include "Player.h"
#include <stdexcept>

Player::Player(int id, int initialX, int initialY, int health, int bullets) :
	RenderableObject(id, initialX, initialY),
	textureLoader(TextureLoader::getInstance()),
	an(textureLoader.getTexture("Soldier_1/Idle.png")),
	facingLeft(false),
	state(IDLE_SOLDIER),
	playSFX(false),
	lastChannel(-1),
	health_(health),
	bullets_(bullets)
{}

Player::~Player() = default;

bool Player::isMoving() const
{
	return this->state == MOVING;
}

int Player::getHealth() const
{
	return this->health_;
}

int Player::getBullets() const
{
	return this->bullets_;
}

void Player::updateState(const SoldierObjectDTO &soldierDTO)
{
	if (soldierDTO.id != this->getID())
		throw std::invalid_argument("Invalid ID");

	this->facingLeft = soldierDTO.facing_left;
	this->setPositionX(soldierDTO.position_x);
	this->setPositionY(soldierDTO.position_y);
	this->health_ = soldierDTO.health;
	this->bullets_ = soldierDTO.bullets;
	this->changeState(soldierDTO.state);
}

void Player::updateState(const ZombieObjectDTO &zombieDTO) {}

void Player::updateState(const GrenadeObjectDTO &grenadeDTO) {}
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

void Player::changeState(const SoldierObjectState &state)
{
	if (this->state == state)
		return;

	this->state = state;

	if (this->state == SHOOTING) {
		this->an.changeTexture(this->textureLoader.getTexture("Soldier_1/Shot_1.png"));
		this->sfx = this->textureLoader.getChunk("Soldier_1/Shot_1.mp3");
		this->sfxLoops = -1;
	} else if (this->state == RELOADING) {
		this->an.changeTexture(this->textureLoader.getTexture("Soldier_1/Recharge.png"));
		this->an.noLoop();
		this->sfx = this->textureLoader.getChunk("Soldier_1/Recharge.mp3");
		this->sfxLoops = 0;
	} else if (this->state == MOVING) {
		this->an.changeTexture(this->textureLoader.getTexture("Soldier_1/Walk.png"));
		this->sfx = this->textureLoader.getChunk("Soldier_1/Walk.mp3");
		this->sfxLoops = -1;
	} else if (this->state == SOLDIER_DEAD) {
		this->an.changeTexture(this->textureLoader.getTexture("Soldier_1/Dead.png"));
		this->an.noLoop();
		this->sfx = this->textureLoader.getChunk("Soldier_1/Dead.mp3");
		this->sfxLoops = 0;
	} else if (this->state == SOLDIER_HURT) {
		this->an.changeTexture(this->textureLoader.getTexture("Soldier_1/Hurt.png"));
		this->sfx = nullptr;
	} else if(this->state == THROWING_GRENADE) {
		this->an.changeTexture(this->textureLoader.getTexture("Soldier_1/Grenade.png"));
		this->sfx = this->textureLoader.getChunk("Soldier_1/Grenade.mp3");
		this->sfxLoops = 0;
	} else {
		this->an.changeTexture(this->textureLoader.getTexture("Soldier_1/Idle.png"));
		this->an.noLoop();
		this->sfx = nullptr;
	}
	this->playSFX = true;
}
