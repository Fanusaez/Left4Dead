#ifndef WEAPON_H_
#define WEAPON_H_

#include <vector>
#include "../game_object.h"

class Weapon {
 private:

 public:
virtual void shoot(std::vector<GameObject*>& shooting_objects,
                   std::uint16_t y_pos_sold, float time) = 0;

virtual void throw_explosive_grenade(std::vector<GameObject*>& shooting_objects, float time) = 0;
virtual void reload() = 0;
virtual bool isFullyLoaded() = 0;
virtual bool empty() = 0;
virtual std::int16_t get_bullets() = 0;
};
#endif  // WEAPON_H_
