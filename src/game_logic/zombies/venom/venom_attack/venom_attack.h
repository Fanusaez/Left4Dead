#ifndef VENOMATTACK_H_
#define VENOMATTACK_H_

#include <cstdint>
#include <vector>

#define CONFIGURATION Configuration::getInstance()

class ZombieState;
class Soldier;

class VenomAttack {
public:
    virtual ZombieState* attack(ZombieState* state, Soldier* soldier_to_attack, float time) = 0;
    virtual std::vector<std::int16_t> get_pos_explosion() = 0;
    virtual bool are_you_long_range_attack() = 0;
};

#endif  // VENOMATTACK_H_
