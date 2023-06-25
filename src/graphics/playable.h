#ifndef GRAPHICS_PLAYABLE_H
#define GRAPHICS_PLAYABLE_H

#include "renderable_object.h"
#include <list>
#include <utility>
#include <string>

class Playable : public RenderableObject {
	int health_;

	int ammo_;

	int explosiveCd;

	int smokeCd;

	int airStrikeCd;

public:
	Playable(int id, int initialX, int initialY, int health, int bullets);

	int getHealth() const;

	int getAmmo() const;

	std::list<std::pair<std::string, int>> getCooldowns() const;

	virtual bool isPlayable() const override;

	virtual ~Playable();

protected:
	void updateHealth(int health);

	void updateAmmo(int ammo);

	void updateExplosiveCd(int cooldown);

	void updateSmokeCd(int cooldown);

	void updateAirStrikeCd(int cooldown);
};

#endif //GRAPHICS_PLAYABLE_H
