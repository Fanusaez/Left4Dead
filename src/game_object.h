#ifndef GAME_OBJECT_H_
#define GAME_OBJECT_H_

#include "weapon.h"

class GameObject {
 private:

 public:
virtual void get_shot(Weapon* weapon) = 0;

};

#endif  // GAME_OBJECT_H_
