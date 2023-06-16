#ifndef ZOMBIEATTACK_H_
#define ZOMBIEATTACK_H_

#include <cstdint>

class ZombieState;
class Soldier;

class ZombieAttack {
public:
    virtual ZombieState* attack(ZombieState* state, Soldier* soldier_to_attack, float time) = 0;
};

#endif  // ZOMBIEATTACK_H_
