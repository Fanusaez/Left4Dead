#include "scout.h"

Scout::Scout(const SoldierObjectDTO &soldierDTO) :
	Playable(soldierDTO.id, soldierDTO.position_x, soldierDTO.position_y,
		 soldierDTO.health, soldierDTO.bullets),
	textureLoader(TextureLoader::getInstance()),
	animation(textureLoader.getTexture("Soldier_3/Idle.png")),
	facingLeft(false),
	state(IDLE_SOLDIER),
	playSFX(false),
	lastChannel(-1)
{
	this->updateExplosiveCd(soldierDTO.time_explosive_grenade);
	this->updateSmokeCd(soldierDTO.time_smoke_grenade);
}

Scout::~Scout()
{}

void Scout::updateState(const SoldierObjectDTO &soldierDTO)
{
	if (soldierDTO.id != this->getID())
		throw std::invalid_argument("Invalid ID");

	this->facingLeft = soldierDTO.facing_left;
	this->setPositionX(soldierDTO.position_x);
	this->setPositionY(soldierDTO.position_y);
	this->updateHealth(soldierDTO.health);
	this->updateAmmo(soldierDTO.bullets);
	this->updateExplosiveCd(soldierDTO.time_explosive_grenade);
	this->updateSmokeCd(soldierDTO.time_smoke_grenade);
	this->changeState(soldierDTO.state);
}

void Scout::updateState(const ZombieObjectDTO &zombieDTO)
{}

void Scout::updateState(const GrenadeObjectDTO &grenadeDTO)
{}

void Scout::update(unsigned int dt)
{
	if (this->state != IDLE_SOLDIER)
		this->animation.update(dt);
}

void Scout::render(SDL2pp::Renderer &renderer, SDL2pp::Rect &dst)
{
	SDL_RendererFlip flip = this->facingLeft ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE;
	this->animation.render(renderer, dst, flip);
}

void Scout::renderAudio(SDL2pp::Mixer &mixer)
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

void Scout::changeState(const SoldierObjectState &state)
{
	if (this->state == state)
		return;

	this->state = state;

	if (this->state == SHOOTING) {
		this->animation.changeTexture(this->textureLoader.getTexture("Soldier_3/Shot_1.png"));
        this->animation.noLoop();
		this->sfx = this->textureLoader.getChunk("Soldier_3/Shot_1.mp3");
		this->sfxLoops = -1;
	} else if (this->state == RELOADING) {
		this->animation.changeTexture(this->textureLoader.getTexture("Soldier_3/Recharge.png"));
		this->animation.noLoop();
		this->sfx = this->textureLoader.getChunk("Soldier_3/Recharge.mp3");
		this->sfxLoops = 0;
	} else if (this->state == MOVING) {
		this->animation.changeTexture(this->textureLoader.getTexture("Soldier_3/Walk.png"));
		this->sfx = this->textureLoader.getChunk("Soldier_1/Walk.mp3");
		this->sfxLoops = -1;
	} else if (this->state == SOLDIER_DEAD) {
		this->animation.changeTexture(this->textureLoader.getTexture("Soldier_3/Dead.png"));
		this->animation.noLoop();
		this->sfx = this->textureLoader.getChunk("Soldier_1/Dead.mp3");
		this->sfxLoops = 0;
	} else if (this->state == SOLDIER_HURT) {
		this->animation.changeTexture(this->textureLoader.getTexture("Soldier_3/Hurt.png"));
		this->sfx = nullptr;
	} else if(this->state == THROWING_GRENADE) {
		this->animation.changeTexture(this->textureLoader.getTexture("Soldier_3/Grenade.png"));
		this->animation.noLoop();
		this->sfx = this->textureLoader.getChunk("Soldier_1/Grenade.mp3");
		this->sfxLoops = 0;
	} else {
		this->animation.changeTexture(this->textureLoader.getTexture("Soldier_3/Idle.png"));
		this->animation.noLoop();
		this->sfx = nullptr;
	}
	this->playSFX = true;
}
