#include "playable.h"

Playable::Playable(int id, int initialX, int initialY, int health, int bullets, int cooldown) :
	RenderableObject(id, initialX, initialY),
	health_(health),
	ammo_(bullets),
	cd(cooldown)
{}

int Playable::getHealth() const
{
	return this->health_;
}

int Playable::getAmmo() const
{
	return this->ammo_;
}

int Playable::getCooldown() const
{
	return this->cd;
}

bool Playable::isPlayable() const
{
	return true;
}

void Playable::updateHealth(int health)
{
	this->health_ = health;
}

void Playable::updateAmmo(int ammo)
{
	this->ammo_ = ammo;
}

void Playable::updateCooldown(int cooldown)
{
	this->cd = cooldown;
}

Playable::~Playable()
{}
