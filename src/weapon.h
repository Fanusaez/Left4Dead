#ifndef WEAPON_H_
#define WEAPON_H_

#include <vector>
#include "game_object.h"

class Weapon {
 private:

 public:
virtual void shoot(std::vector<GameObject*>& shooting_objects,
                   std::uint16_t y_pos_sold) = 0;
};
#endif  // WEAPON_H_
