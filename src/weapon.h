#ifndef WEAPON_H_
#define WEAPON_H_

#include "walker.h"

class Weapon {
 private:

 public:
virtual void shoot(Walker& walker) = 0;
};
#endif  // WEAPON_H_
