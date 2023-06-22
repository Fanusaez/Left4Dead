#ifndef GRAPHICS_PLAYABLE_H
#define GRAPHICS_PLAYABLE_H

#include "renderable_object.h"

class Playable : public RenderableObject {
	int health_;

	int ammo_;

	int cd;
public:
	Playable(int id, int initialX, int initialY, int health, int bullets, int cooldown);

	int getHealth() const;

	int getAmmo() const;

	int getCooldown() const;

	virtual bool isPlayable() const override;

	virtual ~Playable();

protected:
	void updateHealth(int health);

	void updateAmmo(int ammo);

	void updateCooldown(int cooldown);
};

#endif //GRAPHICS_PLAYABLE_H
