#include "playable.h"

Playable::Playable(int id, int initialX, int initialY, int health, int bullets) :
	RenderableObject(id, initialX, initialY),
	health_(health),
	ammo_(bullets),
	explosiveCd(-1),
	smokeCd(-1),
	airStrikeCd(-1)
{}

int Playable::getHealth() const
{
	return this->health_;
}

int Playable::getAmmo() const
{
	return this->ammo_;
}

std::list<std::pair<std::string, int>> Playable::getCooldowns() const
{
	std::list<std::pair<std::string, int>> cds;
	if (this->explosiveCd != -1) {
		std::string text = "Grenade: ";
		cds.push_back(std::pair<std::string, int>(text, this->explosiveCd));
	}
	if (this->smokeCd != -1) {
		std::string text = "Smoke: ";
		cds.push_back(std::pair<std::string, int>(text, this->smokeCd));
	}
	if (this->airStrikeCd != -1) {
		std::string text = "Air Strike: ";
		cds.push_back(std::pair<std::string, int>(text, this->airStrikeCd));
	}
	return cds;
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

void Playable::updateExplosiveCd(int cooldown)
{
	if (cooldown < 0 and cooldown != -1)
		return;
	this->explosiveCd = cooldown;
}

void Playable::updateSmokeCd(int cooldown)
{
	if (cooldown < 0 and cooldown != -1)
		return;
	this->smokeCd = cooldown;
}

void Playable::updateAirStrikeCd(int cooldown)
{
	if (cooldown < 0 and cooldown != -1)
		return;
	this->airStrikeCd = cooldown;
}

Playable::~Playable()
{}
