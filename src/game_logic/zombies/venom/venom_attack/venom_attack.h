#ifndef VENOMATTACK_H_
#define VENOMATTACK_H_

#include <cstdint>
#define CONFIGURATION Configuration::getInstance()

class ZombieState;
class Soldier;

class VenomAttack {
public:
    virtual ZombieState* attack(ZombieState* state, Soldier* soldier_to_attack, float time) = 0;
};

#endif  // VENOMATTACK_H_
