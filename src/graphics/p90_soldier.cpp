#include "p90_soldier.h"

SoldierP90::SoldierP90(int id, int initialX, int initialY, int health, int bullets, int cooldown) :
	Playable(id, initialX, initialY, health, bullets, cooldown),
	textureLoader(TextureLoader::getInstance()),
	animation(textureLoader.getTexture("Soldier_2/Idle.png")),
	facingLeft(false),
	state(IDLE_SOLDIER),
	playSFX(false),
	lastChannel(-1)
{}

SoldierP90::~SoldierP90()
{}

void SoldierP90::updateState(const SoldierObjectDTO &soldierDTO)
{
	if (soldierDTO.id != this->getID())
		throw std::invalid_argument("Invalid ID");

	this->facingLeft = soldierDTO.facing_left;
	this->setPositionX(soldierDTO.position_x);
	this->setPositionY(soldierDTO.position_y);
	this->updateHealth(soldierDTO.health);
	this->updateAmmo(soldierDTO.bullets);
	this->updateCooldown(soldierDTO.time_explosive_grenade);
	this->changeState(soldierDTO.state);
}

void SoldierP90::updateState(const ZombieObjectDTO &zombieDTO)
{}

void SoldierP90::updateState(const GrenadeObjectDTO &grenadeDTO)
{}

void SoldierP90::update(unsigned int dt)
{
	if (this->state != IDLE_SOLDIER)
		this->animation.update(dt);
}

void SoldierP90::render(SDL2pp::Renderer &renderer, SDL2pp::Rect &dst)
{
	SDL_RendererFlip flip = this->facingLeft ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE;
	this->animation.render(renderer, dst, flip);
}

void SoldierP90::renderAudio(SDL2pp::Mixer &mixer)
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

void SoldierP90::changeState(const SoldierObjectState &state)
{
	if (this->state == state)
		return;

	this->state = state;

	if (this->state == SHOOTING) {
		this->animation.changeTexture(this->textureLoader.getTexture("Soldier_2/Shot_1.png"));
		this->sfx = this->textureLoader.getChunk("Soldier_2/Shot_1.mp3");
		this->sfxLoops = -1;
	} else if (this->state == RELOADING) {
		this->animation.changeTexture(this->textureLoader.getTexture("Soldier_2/Recharge.png"));
		this->animation.noLoop();
		this->sfx = this->textureLoader.getChunk("Soldier_2/Recharge.mp3");
		this->sfxLoops = 0;
	} else if (this->state == MOVING) {
		this->animation.changeTexture(this->textureLoader.getTexture("Soldier_2/Walk.png"));
		this->sfx = this->textureLoader.getChunk("Soldier_1/Walk.mp3");
		this->sfxLoops = -1;
	} else if (this->state == SOLDIER_DEAD) {
		this->animation.changeTexture(this->textureLoader.getTexture("Soldier_2/Dead.png"));
		this->animation.noLoop();
		this->sfx = this->textureLoader.getChunk("Soldier_1/Dead.mp3");
		this->sfxLoops = 0;
	} else if (this->state == SOLDIER_HURT) {
		this->animation.changeTexture(this->textureLoader.getTexture("Soldier_2/Hurt.png"));
		this->sfx = nullptr;
	} else if(this->state == CALLING_AIR_STRIKE) {
		this->animation.changeTexture(this->textureLoader.getTexture("Soldier_2/Grenade.png"));
		this->animation.noLoop();
		this->sfx = this->textureLoader.getChunk("Soldier_2/Grenade.mp3");
		this->sfxLoops = 0;
	} else {
		this->animation.changeTexture(this->textureLoader.getTexture("Soldier_2/Idle.png"));
		this->animation.noLoop();
		this->sfx = nullptr;
	}
	this->playSFX = true;
}
